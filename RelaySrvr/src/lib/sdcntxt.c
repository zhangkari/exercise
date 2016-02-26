/**************************
 * file:    sdcntxt.h
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <comm.h>
#include <protocol.h>
#include <config.h>
#include <sdcntxt.h>
#include <utility.h>

struct sdcntxt_t {
	int fd_srv_pub;		// fd connected to remote public server
	int fd_srv_local;	// fd related local server
	int fd_epoll;		// epoll fd
	uint32 token;		// token assigned by remote server
} slave_cntxt;

/**
 * Return the sdcntxt_t by default value
 */
sdcntxt_t* default_slave_cntxt()
{
	sdcntxt_t *cntxt = (sdcntxt_t *)calloc(1, sizeof(sdcntxt_t));
	if (NULL == cntxt) {
		Log("Failed calloc mem for slave_cntxt\n");
		return NULL;
	}

	int fd = prepare_tcp_client(SERVER_IP, DEFAULT_PORT);
	if (fd < 0) {
		Log("Failed prepare tcp client socket\n");
		free (cntxt);
		return NULL;
	}
	cntxt->fd_srv_pub = fd;

	do {
		msgheader_t header;
		memset(&header, 0, sizeof(header));
		header.message_type = REQ_CONNECT;
		header.device_type = DEVICE_SLAVE;
		header.token = 0;

		if (send(fd, &header, sizeof(header), 0) != sizeof(header)) {
			LogE("Failed send msgheader\n");
			break;
		}

		memset(&header, 0, sizeof(header));
		if (recv(fd, &header, sizeof(header), 0) != sizeof(header)) {
			Log("Failed recv msgheader\n");
			break;
		}

		int token = ntohl(header.token);
		printf("token:%d\n", token);
		if (token <= 0) {
			Log("server response error msg\n");
			break;
		} 

		struct sockaddr_in addr;
		int addr_len = sizeof(addr);
		if (getsockname(fd, (struct sockaddr*)&addr, &addr_len) < 0) {
			Log("Failed getsockname\n");
			break;
		}
		else {
			Log("%s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		}

		int opt = 1;
		if (setsockopt(
					fd, 
					SOL_SOCKET, 
					SO_REUSEADDR, 
					&opt, 
					sizeof(opt)) < 0) {
			Log("Failed set socket reuse addr\n");
			break;
		}

		int fd_srvr = prepare_tcp_server(addr.sin_port);
		if (fd_srvr < 0) {
			Log("Failed create server socket\n");
			break;
		}

		cntxt->fd_srv_local = fd_srvr;
		return cntxt;
	} while (0);

	close(fd);
	free (cntxt);
	return NULL;
}

/**
 * Return the sdcntxt_t by the config file
 */
sdcntxt_t* create_slave_cntxt(const char *path) 
{
	return NULL;
}

/**
 * Start slave device
 * Return:
 *      0  success
 *      -1 failed
 */
int sd_start(sdcntxt_t *cntxt)
{
	VALIDATE_NOT_NULL(cntxt);

#define EPOLL_SIZE 32
	cntxt->fd_epoll = epoll_create(EPOLL_SIZE);
	if (cntxt->fd_epoll < 0) {
		LogE("Failed epoll_create()");
		return -1;
	}

	struct epoll_event ev_local;
	memset(&ev_local, 0, sizeof(ev_local));
	ev_local.data.fd = cntxt->fd_srv_local;
	ev_local.events = EPOLLIN;
	if (epoll_ctl(cntxt->fd_epoll,
				EPOLL_CTL_ADD,
				cntxt->fd_srv_local,
				&ev_local) , 0) {
		LogE("Failed add fd_srv_local to epoll:%s", strerror(errno));
		return -1;
	}

	struct epoll_event ev_pub;
	memset(&ev_pub, 0, sizeof(ev_pub));
	ev_pub.data.fd = cntxt->fd_srv_pub;
	ev_pub.events = EPOLLIN;
	if (epoll_ctl(cntxt->fd_epoll,
				EPOLL_CTL_ADD,
				cntxt->fd_srv_pub,
				&ev_pub) , 0) {
		LogE("Failed add fd_srv_pub to epoll:%s", strerror(errno));
		return -1;
	}

	return 0;
}

static int process_public_server(sdcntxt_t *cntxt) {
	VALIDATE_NOT_NULL(cntxt);
	Log("process public server\n");
	msgheader_t header;
	int nrecv;
	do {
		nrecv = recv(cntxt->fd_srv_pub, &header, sizeof(header), 0);
		if (nrecv != sizeof(header)) {
			Log("Failed recv message header\n");
			break;
		}

		int type = ntohl(header.message_type);
		if (type != REQ_RELAY) {
			Log("Recv invalid request relay\n");
			break;
		}

		Log("recv req_relay from public server\n");

		uint32 ip = header.ip;
		char buffer[32];
		memset(buffer, 0, 32);
		char *ptr = format_ip(ip, buffer);
		int port = header.port;
		port = ntohs(port);
		Log("master device:%s:%d\n", ptr, port);

		// NAT map
		prepare_tcp_client(ptr, port);
		Log("sent package to master device NAT\n");

		header.message_type = RES_RELAY;
		if(send(cntxt->fd_srv_pub, &header, sizeof(header), 0) <= 0) {
			Log("Failed send res_relay to public server\n");
		}
		Log("sent res_relay to public server\n");
		return 0;

	} while (0);

	header.message_type = INVALID;
	send(cntxt->fd_srv_pub, &header, sizeof(header), 0);
	return -1;
}

static int process_master_device(sdcntxt_t *cntxt, int fd) {
	VALIDATE_NOT_NULL(cntxt);

	Log("process master device\n");

	return -1;
}

static int accept_master_connection(sdcntxt_t *cntxt) {
	VALIDATE_NOT_NULL(cntxt);

	Log("accept_master_connection()\n");

	return 0;
}

/**
 * Poll slave device
 * Return:
 *      0  success
 *      -1 failed
 */
int sd_loop(sdcntxt_t *cntxt)
{
	VALIDATE_NOT_NULL(cntxt);

#define MAX_EVENTS 16
#define WAIT_TIMEOUT 10
	struct epoll_event ev[MAX_EVENTS];
	int ret = epoll_wait(cntxt->fd_epoll, ev, MAX_EVENTS, WAIT_TIMEOUT);
	int i;
	for (i = 0; i < ret; ++i) {
		if (ev[i].data.fd == cntxt->fd_srv_local) {
			accept_master_connection(cntxt);
			continue;
		}

		if (ev[i].events & EPOLLIN) {
			int fd = ev[i].data.fd;
			if (fd == cntxt->fd_srv_pub) {
				if (process_public_server(cntxt) < 0) {
					Log("Failed process public server\n");
				}
				continue;
			} 
			if (process_master_device(cntxt, fd) < 0) {
				Log("Failed process master device\n");
			}
		}
	}

	return 0;
} 
/**
 * Free the context 
 */
void free_sdcntxt(sdcntxt_t *cntxt)
{
	if (NULL != cntxt) {
		if (epoll_ctl(cntxt->fd_epoll,
					EPOLL_CTL_DEL,
					cntxt->fd_srv_local,
					NULL) < 0) {
			Log("Failed del fd_srv_local from epoll\n");
		}

		if (epoll_ctl(cntxt->fd_epoll,
					EPOLL_CTL_DEL,
					cntxt->fd_srv_pub,
					NULL) < 0) {
			Log("Failed del fd_srv_pub from epoll\n");
		}

		close (cntxt->fd_srv_pub);
		close (cntxt->fd_srv_local);
		close (cntxt->fd_epoll);
		cntxt->token = 0;
		free(cntxt);
	}
}

/**
 * dumplicate sdcntxt
 */
void dump_sdcntxt(sdcntxt_t *cntxt)
{

}
