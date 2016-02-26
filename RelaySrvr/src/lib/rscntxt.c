/**************************
 * file:    rscntxt.c
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <comm.h>
#include <linklist.h>
#include <protocol.h>
#include <rscntxt.h>

typedef struct connection_t {
	enum {
		STATUS_INIT = 0,
		STATUS_OK,
		STATUS_DISCONNECT,
		STATUS_ERROR
	} conn_status;
	uint32 token;
	uint32 conn_fd;
} connection_t;

struct rscntxt_t {
	uint16 port;			//
	uint16 backlog;			//
	int32 fd_srvr;			//
	int32 fd_epoll;			//
	linklist_t *conn_list;	// slave device connection list
	uint32 heartbeat_cycle; // ms
	uint32 min_token;		// 
	uint32 curr_max_token;	//
};

PRIVATE int compare_conn(void *p1, void *p2)
{
	VALIDATE_NOT_NULL2(p1, p2);
	connection_t *conn1 = (connection_t *)p1; 
	connection_t *conn2 = (connection_t *)p2; 
	if (conn1->conn_fd == conn2->conn_fd) {
		return 0;
	}

	return -1;
}

/**
 * new a connection
 */
connection_t* new_connection() {
	connection_t *conn = (connection_t *)calloc(sizeof(*conn), 1);
	if (NULL == conn) {
		return NULL;
	}

	return conn;
}

/**
 * free the connection
 */
void free_connection(connection_t *conn) {
	if (NULL != conn) {
		if (conn->conn_fd > 0) {
			close(conn->conn_fd);
			conn->conn_fd = 0;
		}

		conn->conn_status = STATUS_ERROR;
		free(conn);
	}
}

/**
 * Return the rscntxt_t by default value
 */
rscntxt_t* default_context()
{
	rscntxt_t *cntxt = (rscntxt_t *)calloc(sizeof(*cntxt), 1);
	if (NULL == cntxt) {
		return NULL;
	}

	cntxt->conn_list = init_linklist();
	if (NULL == cntxt->conn_list) {
		LogE("Failed init conn_list");
		free (cntxt);
		cntxt = NULL;
		return NULL;
	}

	cntxt->port = DEFAULT_PORT;
	cntxt->backlog = DEFAULT_BACKLOG;
	cntxt->heartbeat_cycle = HEART_BEAT_CYCLE;
	cntxt->min_token = 400;
	cntxt->curr_max_token = 400;

	return cntxt;
}

/**
 * Return the rscntxt_t by the config file
 */
rscntxt_t* create_context(const char *path)
{
	LogE("Not implemented yet!");
	return NULL;
}

/**
 * Free the context 
 */
void free_context(rscntxt_t *cntxt)
{
	if (NULL != cntxt) {
		if (NULL != cntxt->conn_list) {
			free_linklist(cntxt->conn_list);
			cntxt->conn_list = NULL;
		}

		if (epoll_ctl(
					cntxt->fd_epoll, 
					EPOLL_CTL_DEL, 
					cntxt->fd_srvr, 
					NULL) < 0) {
			LogE("Failed del fd_srvr from epoll");
		}

		close(cntxt->fd_srvr);
		close(cntxt->fd_epoll);

		free (cntxt);
		cntxt = NULL;
	}
}

/**
 * Start relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int rs_start(rscntxt_t *cntxt)
{
	if (NULL == cntxt) {
		LogE("NULL Pointer");
		return -1;
	}

	dump_context(cntxt);

	cntxt->fd_srvr = prepare_tcp_server(cntxt->port, cntxt->backlog);
	if (cntxt->fd_srvr < 0) {
		LogE("Failed prepare tcp server");
		return -1;
	}

#define EPOLL_MAX_SIZE 32
	cntxt->fd_epoll = epoll_create(EPOLL_MAX_SIZE);
	if (cntxt->fd_epoll < 0) {
		LogE("Failed epoll_create()");
		return -1;
	}

	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.data.fd = cntxt->fd_srvr;
	ev.events = EPOLLIN;
	if (epoll_ctl(cntxt->fd_epoll, 
				EPOLL_CTL_ADD, 
				cntxt->fd_srvr,
				&ev) < 0) {
		LogE("Failed add fd_srvr to epoll:%s", strerror(errno));
		return -1;
	}

	return 0;
}

static int proc_admin_connect(int fd) {
	Log("proc admin connect\n");

	return 0;
}

static connection_t* find_connection(
		rscntxt_t *cntxt,
		uint32 token) {

	if (NULL == cntxt || token == 0) {
		return NULL;
	}

	connection_t *conn = NULL;
	linklist_s *list = cntxt->conn_list;
	while (list) {
		conn = (connection_t *)list->elem; 
		if (NULL != conn && token == conn->token) {

		
			return conn;
		}

		list = list->next;
	}

	return NULL;
}

static int proc_master_connect(int fd, int token, rscntxt_t *cntxt) {
	Log("proc master connect\n");
	connection_t *conn = find_connection(cntxt, token);
	if (conn == NULL) {
		Log("Invalid token:%d from the master device\n", token);
		close (fd);
		return -1;
	} 

	int fd_slave = conn->conn_fd;
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	if (getpeername(fd, (struct sockaddr *)&addr, &addr_len) < 0) {
		Log("Failed getsockname of master device");
		close (fd);	
		return -1;
	}

	uint32 ip = addr.sin_addr.s_addr;
	int port = addr.sin_port;
	msgheader_t header;
	memset(&header, 0, sizeof(header));
	header.message_type = htonl(REQ_RELAY);
	header.ip = ip;
	header.port = port;
	int nsize = sizeof(header);
	if(send(fd_slave, &header, nsize, 0) <= 0) {
		Log("Failed send resquest relay to slave device\n");
		return -1;
	}

	Log("sent req_relay to slave device\n");

	if (recv(fd_slave, &header, nsize, 0) <= 0) {
		Log("Failed recv slave device response reply\n");
		return -1;
	}

	if (header.message_type != RES_RELAY) {
		Log("Slave device response an invalid reply\n");
		return -1;
	}

	Log("recv res_relay from slave device\n");

	if (getpeername(fd_slave, (struct sockaddr *)&addr, &addr_len) < 0) {
		Log("Failed getsockname of slave device");
		close (fd);	
		return -1;
	}
	ip = addr.sin_addr.s_addr;
	port = addr.sin_port;
	header.ip = ip;
	header.port = port;
	header.token = htonl(token);
	if (send(fd, &header, nsize, 0) != nsize) {
		Log("Failed send master response message");
		close(fd);
		return -1;
	}

	return 0;
}

static int proc_slave_connect(
		int fd, 
		rscntxt_t *cntxt) {

	Log("proc slave connect\n");

	msgheader_t header;
	header.message_type = RES_CONNECT;
	header.device_type = DEVICE_SLAVE;
	header.token = 0;

	++cntxt->curr_max_token;
	uint32 token = cntxt->curr_max_token;
	connection_t *conn = new_connection();
	if (NULL == conn) {
		LogE("Failed new connection");
		return -1;
	}

	conn->token = token;
	conn->conn_fd = fd; 
	if (add_list_elem(cntxt->conn_list, conn) < 0) {
		LogE("Failed add conn to conn_list");
		free_connection(conn);
		conn = NULL;
		return -1;
	} 

	header.token = htonl(conn->token);
	if (send(fd, &header, sizeof(header),0) != sizeof(header)) {
		LogE("Failed send RES_CONNECT to client");
		return -1;
	}
	printf("token:%d\n", conn->token);

	return 0;
}

static int accept_connection(rscntxt_t *cntxt) {
	if (NULL == cntxt) {
		return -1;
	}

	struct sockaddr_in addr;
	int len = sizeof(addr);
	int fd = accept(cntxt->fd_srvr, (struct sockaddr *)&addr, &len);
	if (fd < 0) {
		Log("Failed accept client's connect");
		return -1;
	}

	Log("accept %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(cntxt->fd_epoll, EPOLL_CTL_ADD, fd, &ev) < 0) {
		LogE("Failed add fd to epoll");
		return -1;
	}

	return 0;
}

static int read_client(int fd, rscntxt_t *cntxt) {
	if (NULL == cntxt) {
		return -1;
	}

	msgheader_t header;
	int nrecv = recv(fd, &header, sizeof(header), 0);
	if(nrecv < 0) {
		LogE("Failed recv msg header:%s", strerror(errno));
		close(fd);
		return -1;
	}

	if (0 == nrecv) {
		struct sockaddr_in addr;
		int len = sizeof(addr);
		getpeername(fd, (struct sockaddr *)&addr, &len);
		Log("client %s disconnect\n", inet_ntoa(addr.sin_addr) );

		if (epoll_ctl(cntxt->fd_epoll, EPOLL_CTL_DEL, fd, NULL) < 0) {
			LogE("Failed delete disconnected client fd"); 
		}
		close(fd);

		connection_t conn;
		conn.conn_fd = fd;
		remove_list_elem(cntxt->conn_list, &conn, compare_conn);
		return 0;
	} 

	if (validate_msgheader(&header) < 0) {
		LogE("Invalid msg header");
		close(fd);
		return -1;
	}

	if (REQ_CONNECT == header.message_type
			&& DEVICE_SLAVE == header.device_type) {
		if (proc_slave_connect(fd, cntxt) < 0) {
			LogE("Failed process slave device connect");
			close(fd);
			return -1;
		}
	}
	else if (REQ_CONNECT == header.message_type
			&& DEVICE_MASTER == header.device_type) {
		if (proc_master_connect(fd, ntohl(header.token), cntxt) < 0) {
			LogE("Failed process master device relay");
			close(fd);
			return -1;
		}
	}
	else if (DEVICE_ADMIN == header.device_type) {
		proc_admin_connect(fd);
	}

	return 0;
}

/**
 * Poll relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int rs_loop(rscntxt_t *cntxt)
{
	if (NULL == cntxt) {
		LogE("NULL Pointer");
		return -1;
	}

#define MAX_EVENTS 16
#define WAIT_TIMEOUT 10
	struct epoll_event ev[MAX_EVENTS];
	int ret = epoll_wait(cntxt->fd_epoll, ev, MAX_EVENTS, WAIT_TIMEOUT); 
	int i;
	for (i = 0; i < ret; ++i) {
		if (ev[i].data.fd == cntxt->fd_srvr) {
			accept_connection(cntxt);
			continue;
		}

		int nread = read_client(ev[i].data.fd, cntxt);
		if (nread < 0) {
			LogE("Failed read client");
		}
	}

	return 0;
}

/**
 * dumplicate rscntxt
 */
void dump_context(rscntxt_t *cntxt)
{
	if (NULL == cntxt) {
		LogE("NULL pointer");
		return;
	}

	Log("port:%d\n", cntxt->port);
	Log("backlog:%d\n", cntxt->backlog);
	Log("heart beat:%d ms\n", cntxt->heartbeat_cycle);
}

