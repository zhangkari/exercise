#include "ip_packet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(linux)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

ip_packet_st* peek_ip_packet(buffer_st* buffer, ip_packet_st* ip)
{
	if (NULL == buffer) {
		fprintf(stdout, "NULL pointer Exception %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (NULL == ip) {
		ip = (ip_packet_st*)malloc(sizeof(ip_packet_st));
		if(NULL == ip)
			return NULL;
	}

	ip->header = buffer->base + sizeof(mac_header_st);
	ip->length = buffer->length - sizeof(mac_header_st) - sizeof(ip_header_st);
	ip->data = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st);

	return ip;
}

static char* print_ip_addr(uint32 addr) {
	struct in_addr addr_st;
	memcpy(&addr_st, &addr, sizeof(addr));

	return inet_ntoa(addr_st);
}

void print_ip_header(ip_header_st* header)
{
	if (NULL == header) {
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return ;
	}

	fprintf(stdout, "++++++++++++ ip packet ++++++++\n");	
	fprintf(stdout, "version:%d\n", header->version);
	fprintf(stdout, "headlen:%d\n", header->headlen);
	fprintf(stdout, "tos:%d\n", header->tos);
	fprintf(stdout, "totalen:%d\n", ntohs(header->total));
	fprintf(stdout, "id:%d\n", ntohs(header->id));
	uint16 offset = ntohs(header->offset);
	fprintf(stdout, "flag:%x\n", offset & 0x07);
	fprintf(stdout, "offset:%x\n", offset >> 3);	
	fprintf(stdout, "ttl:%d\n", header->ttl);
	fprintf(stdout, "protocol:%d", header->protocol);
	switch (header->protocol) {
		case PROTO_ICMP:
			fprintf(stdout, " (ICMP)\n");
			break;

		case PROTO_IGMP:
			fprintf(stdout, " (IGMP)\n");
			break;

		case PROTO_UDP:
			fprintf(stdout, " (UDP)\n");
			break;

		case PROTO_TCP:
			fprintf(stdout, " (TCP)\n");
			break;
	}
	fprintf(stdout, "checksum:%x\n", header->checksum);
	fprintf(stdout, "src addr:%s\n", print_ip_addr(header->srcaddr));
	fprintf(stdout, "dst addr:%s\n", print_ip_addr(header->dstaddr));

	fprintf(stdout, "+++++++++++++++++++++++++++++++\n");	

	return ;
}

