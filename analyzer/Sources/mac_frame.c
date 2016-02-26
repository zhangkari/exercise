#include "mac_frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mac_frame_st* peek_mac_frame(buffer_st* buffer, mac_frame_st* frame)
{
	if (NULL == buffer) {
		fprintf(stdout, "NULL pointer Exception %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (NULL == frame) {
		frame = (mac_frame_st*)malloc(sizeof(mac_frame_st));
		if(NULL == frame)
		{
			return NULL;
		}
	}

	if (buffer->length > MAX_MAC_FRAME_SIZE || buffer->length < MIN_MAC_FRAME_SIZE) {
		fprintf(stdout, "Invalid mac frame size %d %s:%d\n", buffer->length, __FILE__, __LINE__);
		return NULL;
	}

	frame->header = buffer->base;
	frame->length = buffer->length - sizeof(mac_header_st);
	frame->data = buffer->base + sizeof(mac_header_st);

	return frame;
}


void print_mac_header(mac_header_st* header)
{
	if (NULL == header) {
	fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return;
	}

	fprintf(stdout, "------------ mac frame ------------\n");
	fprintf(stdout, "src addr:%02x-%02x-%02x-%02x-%02x-%02x\n",
		header->src_addr[0], header->src_addr[1], header->src_addr[2],
		header->src_addr[3], header->src_addr[4], header->src_addr[5]
		);
	fprintf(stdout, "dst addr:%02x-%02x-%02x-%02x-%02x-%02x\n",
		header->dst_addr[0], header->dst_addr[1], header->dst_addr[2],
		header->dst_addr[3], header->dst_addr[4], header->dst_addr[5]
		);

	uint16 type = ntohs(header->type);
	fprintf(stdout, "type:%x", type);
	if (TYPE_IP == type) {
		fprintf(stdout, " (IP)\n");
	}
	else if(TYPE_ARP == type) {
		fprintf(stdout, " (ARP)\n");
	}

	fprintf(stdout, "-----------------------------------\n");

	return;
}
