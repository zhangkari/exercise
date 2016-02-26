#ifndef __TCP__MESSAGE__H__
#define __TCP__MESSAGE__H__

#include "type.h"
#include "buffer.h"
#include "byteorder.h"

#ifdef _WIN32
#pragma packed 1
#endif

typedef struct
{
	uint16 srcport;
	uint16 dstport;
	uint32 seq;
	uint32 ack_seq;
#if   defined (__LITTLE__ENDIAN__)
	uint16 	res: 4,
		off: 4,
		fin: 1,		
		syn: 1,
		rst: 1,
		psh: 1,
		ack: 1,
		urg: 1,
		ece: 1,
		cwr: 1;
#elif defined (__BIG__ENDIAN__)
	uint16	off: 4,
		res: 4,
		cwr: 1,
		ece: 1,
		urg: 1,
		ack: 1,
		psh: 1,
		rst: 1,
		syn: 1,
		fin: 1;
#else
#error "Error in byteorder.h, no endian defined"
#endif
	uint16 window;
	uint16 check;
	uint16 urg_ptr;
#if   defined(_WIN32)
} tcp_header_st;
#pragma unpack

#elif defined(linux)
} __attribute__((packed, aligned(1))) tcp_header_st;
#endif


typedef struct
{
	tcp_header_st* header;
	void* data;
	uint32 length;
} tcp_message_st;

tcp_message_st* peek_tcp_message(buffer_st* buffer, tcp_message_st* tcp);
void print_tcp_header(tcp_header_st* header);

#endif
