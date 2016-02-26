#include "udp_datagram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

udp_datagram_st* peek_udp_datagram(buffer_st* buffer, udp_datagram_st* udp)
{
	if (NULL == buffer) {
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (NULL == udp) {
		udp = (udp_datagram_st*)malloc(sizeof(udp_datagram_st));
		if (NULL == udp) {
			return NULL;
		}
	}

	udp->header = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st);
	udp->data = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st) + sizeof(udp_header_st);
	udp->length = buffer->length - sizeof(mac_header_st) - sizeof(ip_header_st) - sizeof(udp_header_st);

	return udp;
}


bool free_udp_datagram(udp_datagram_st* udp)
{
	if (NULL != udp) {
		if (NULL != udp->header) {
			free(udp->header);
			udp->header = NULL;
		}
		if (NULL != udp->data) {
			free_buffer(udp->data);
		}
		free(udp);
		udp = NULL;
	}

	return true;
}

void print_udp_header(udp_header_st* header)
{
	if (NULL == header) {
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return;
	}

	fprintf(stdout, "********** UDP *********\n");
	fprintf(stdout, "src port:%d\n", ntohs(header->srcport));
	fprintf(stdout, "dst port:%d\n", ntohs(header->dstport));
	fprintf(stdout, "length:%d\n", ntohs(header->length));
	fprintf(stdout, "checksum:%x\n", ntohs(header->checksum));
	fprintf(stdout, "************************\n");

	return ;
}
