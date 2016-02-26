#ifndef __HTTP__MESSAGE__H__
#define __HTTP__MESSAGE__H__

#include "type.h"
#include "buffer.h"

#ifndef HTTP_REQUEST
#define HTTP_REQUEST 0
#endif

#ifndef HTTP_RESPONSE
#define HTTP_RESPONSE 1
#endif


typedef struct
{

}http_request_header;

typedef struct
{

}http_response_header;

#pragma packed 1
typedef struct
{
	void*  data;	
	uint32 length;
} http_message_st;

http_message_st* peek_http_message(buffer_st* data, http_message_st* http);
void print_http_message(http_message_st* http);

#endif
