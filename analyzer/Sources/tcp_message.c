#include "type.h"
#include "buffer.h"
#include "byteorder.h"
#include "mac_frame.h"
#include "ip_packet.h"
#include "tcp_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tcp_message_st* peek_tcp_message(buffer_st* buffer, tcp_message_st* tcp)
{
	if (NULL == buffer) {
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (NULL == tcp) {
		tcp = (tcp_message_st*)malloc(sizeof(tcp_message_st));
		if(NULL == tcp)
			return NULL;
	}

	tcp->header = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st);
	tcp->data = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st) + sizeof(tcp_header_st);
	tcp->length = buffer->length - sizeof(mac_header_st) - sizeof(ip_header_st) - sizeof(tcp_header_st);

	return tcp;
}


void print_tcp_header(tcp_header_st* header)
{
	if (NULL == header) {
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return;
	}

	fprintf(stdout, "~~~~~~~~ TCP ~~~~~~~~\n");
	fprintf(stdout, "src port:%d\n", ntohs(header->srcport));
	fprintf(stdout, "dst port:%d\n", ntohs(header->dstport));
	fprintf(stdout, "seq:%d\n", ntohl(header->seq));
	fprintf(stdout, "seq ack:%d\n", ntohl(header->ack_seq));
	fprintf(stdout, "offset:%d\n", header->off * 4);
	fprintf(stdout, "reserve:%d\n", header->res);
	fprintf(stdout, "cwr:%d\n", header->cwr);
	fprintf(stdout, "ece:%d\n", header->ece);
	fprintf(stdout, "urg:%d\n", header->urg);
	fprintf(stdout, "ack:%d\n", header->ack);
	fprintf(stdout, "psh:%d\n", header->psh);
	fprintf(stdout, "rst:%d\n", header->rst);
	fprintf(stdout, "syn:%d\n", header->syn);
	fprintf(stdout, "fin:%d\n", header->fin);
	fprintf(stdout, "window:%d\n", ntohs(header->window));
	fprintf(stdout, "check:%x\n", ntohs(header->check));
	fprintf(stdout, "urg_ptr:%x\n", ntohs(header->urg_ptr));
	fprintf(stdout, "~~~~~~~~~~~~~~~~~~~~~\n");

	return ;
}

