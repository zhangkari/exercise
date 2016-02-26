/*******************************
 * file name:   socketWrapper.h
 * description: wrap socket api 
 * date:        2015-01-15
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#ifndef __SOCKETWRAPPER__H__
#define __SOCKETWRAPPER__H__

/**
 * connect to the specified server
 * params:
		ip:
		port:
 * return:
		success >=0
		failed -1
 */
int prepare_tcp_client(char *ip, int port);

/**
 * create a tcp server socket and listen
 * params:
 *      port:   server's port
 *      blog:   for listen(fd, blog)
 * return:
 *      On success, a file descriptor for the new socket
 *      On error, -1 is returned
 */
int prepare_tcp_server(int port, int backlog);

/**
 * send data, wrapped send(fd, data, len, MSG_DONTWAIT)
 */
int send_data(int fd, void *data, int len);

/**
 * recv data, wrapped recv(fd, data, len, MSG_DONTWAIT)
 */
int recv_data(int fd, void *data, int len);

#endif
