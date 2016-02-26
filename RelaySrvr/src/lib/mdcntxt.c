/**************************
 * file:    mdcntxt.h
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <config.h>
#include <mdcntxt.h>
#include <protocol.h>

struct mdcntxt_t {
	uint32 fd_server;	// fd connected to server
	uint32 fd_slave;	// fd connected to slave device
	uint32 token;		// token assigned by slave device
};

/**
 * Return the mdcntxt_t by default value
 */
mdcntxt_t* default_master_cntxt(int token)
{
	mdcntxt_t *cntxt = (mdcntxt_t*)calloc(1, sizeof(mdcntxt_t));
	if (NULL == cntxt) {
		Log("Failed calloc mem for mdcntxt_t\n");
		return NULL;
	}
	cntxt->token = token;
	return cntxt;
}

/**
 * Return the mdcntxt_t by the config file
 */
mdcntxt_t* create_master_cntxt(const char *path)
{
	return NULL;
}

/**
 * Start master device
 * Return:
 *      0  success
 *      -1 failed
 */
int md_start(mdcntxt_t *cntxt)
{
	VALIDATE_NOT_NULL(cntxt);

	int fd = prepare_tcp_client(SERVER_IP, DEFAULT_PORT);
	if (fd < 0) {
		Log("Failed prepare tcp client socket\n");
		return -1;
	}

	do {
		msgheader_t header;
		memset(&header, 0, sizeof(header));
		header.message_type = REQ_CONNECT;
		header.device_type = DEVICE_MASTER;
		header.token = cntxt->token;
		header.port = htons(DEFAULT_PORT);
		header.ip = 0x00;

		if (send(fd, &header, sizeof(header), 0) != sizeof(header)) {
			Log("Failed send req_connect msgheader");
			break;
		}

		Log("send req_connect to public server finish.\n");

		memset(&header, 0, sizeof(header));
		if (recv(fd, &header, sizeof(header), 0) != sizeof(header)) {
			Log("Failed recv res_connect msgheader");
			break;
		}

		int token = ntohl(header.token);
		int port =  ntohs(header.port);
		Log("public server reply res_connect:token=%d, port=%d\n", token, port);

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr) );
		addr.sin_addr.s_addr = header.ip;

		fd = prepare_tcp_client(inet_ntoa(addr.sin_addr), ntohs(header.port));
		if (fd < 0) {
			Log("Failed create socket to connect slave device");
			break;
		}

		char msg[256];
		int nrecv = recv(fd, msg, 256, 0);
		if (nrecv > 0) {
			msg[nrecv] = 0;
			Log("recv msg:%s\n", msg);
		}
		else {
			LogE("Failed recv phone msg");
		}

		return 0;

	} while (0);

	close (fd);
	return -1;
}

/**
 * Poll master device 
 * Return:
 *      0  success
 *      -1 failed
 */
int md_loop(mdcntxt_t *cntxt)
{
	return 0;
}

/**
 * Free the context 
 */
void free_mdcntxt(mdcntxt_t *cntxt)
{
	if (NULL != cntxt) {
		close (cntxt->fd_server);
		close (cntxt->fd_slave);
		cntxt->token = 0;
		free (cntxt);
	}
}

/**
 * dumplicate mdcntxt
 */
void dump_mdcntxt(mdcntxt_t *cntxt)
{

}
