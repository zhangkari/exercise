#include "mac_frame.h"
#include "ip_packet.h"
#include "tcp_message.h"
#include "http_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

http_message_st* peek_http_message(buffer_st* buffer, http_message_st* http)
{
	if(NULL == buffer)
	{
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	if(NULL == http)
	{
		http = (http_message_st*)malloc(sizeof(http_message_st));
		if(NULL == http)
			return NULL;
	}

	http->length = buffer->length - sizeof(mac_header_st) - sizeof(ip_header_st)-sizeof(tcp_header_st);
	http->data = buffer->base + sizeof(mac_header_st) + sizeof(ip_header_st) + sizeof(tcp_header_st);

	return http;
}

void print_http_message(http_message_st* http)
{
	if(NULL == http)
	{
		fprintf(stdout, "NULL pointer exception %s:%d\n", __FILE__, __LINE__);
		return;
	}
	printf("length=%d\n", http->length);
	fprintf(stdout, "^^^^^^ HTTP ^^^^\n");

	if(NULL != http->data)
	{
		fprintf(stdout, "http data:\n");
		fprintf(stdout, "%s\n", (char*)http->data);
	}
	fprintf(stdout, "^^^^^^^^^^^^^^^^\n");
}
