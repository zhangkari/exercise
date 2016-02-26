/*******************************
 * file name:	socketWrapper.c
 * description: wrap socket api 
 * date:		2015-01-15
 * author:		kari.zhang
 *
 * modifications:
 *
 * ****************************/

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <comm.h>
#include <socketWrapper.h>

/**
 * connect to the specified server
 * params:
		ip:
		port:
 * return:
		success >=0
		failed -1
 */
int prepare_tcp_client(char *ip, int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		Log("Failed create socket\n");
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	int flags;
	flags = fcntl(fd, F_GETFL, 0);
//	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	int ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0 && ret != EINPROGRESS) {
		Log("Failed connect to server\n");
		close(fd);
		return -1;
	}

	flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL,  flags & ~O_NONBLOCK);

	return fd;
}

/**
 * create a tcp server socket and listen
 * params:
 *		port:	server's port
 *		backlog: for listen(fd, backlog)
 * return:
 *		On success, a file descriptor for the new socket
 *		On error, -1 is returned
 */
int prepare_tcp_server(int port, int backlog)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        LogE("Failed create server socket");
        return -1;
    }

    struct sockaddr_in addr;	
    memset(&addr, 0, sizeof(struct sockaddr_in) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        LogE("Failed set socket reuse addr");
    }

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        LogE("Failed bind server socket:%s", strerror(errno));
        close(fd);
        return -1;
    }

    if (listen(fd, backlog) < 0) {
        LogE("Failed listen server socket");
        close(fd);
        return -1;
    }

    return fd;
}

/**
 * send data, wrapped send(fd, data, len, MSG_DONTWAIT)
 */
int send_data(int fd, void *data, int len)
{
    return send(fd, data, len, 0 /*MSG_DONTWAIT*/);
}

/**
 *recv edata, wrapped recv(fd, data, len, MSG_DONTWAIT)
 */
int recv_data(int fd, void *data, int len)
{
    int fin = 0, n = 0;
    do {
        n = recv(fd, (char *)data + fin, len - fin, 0 /* MSG_DONTWAIT*/);
        if (n <= 0) {
            return n;
        }

        fin += n;

    } while (fin < len);

    return fin;
}
