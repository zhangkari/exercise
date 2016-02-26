#ifndef __UDP_DATAGRAM__H__
#define __UDP_DATAGRAM__H__

#include "type.h"
#include "buffer.h"
#include "mac_frame.h"
#include "ip_packet.h"
	
#ifdef _WIN32
#pragma packed 1
#endif

typedef struct
{
  uint16 srcport;
  uint16 dstport;
  uint16 length;
  uint16 checksum;

#if defined(_WIN32)
} udp_header_st;
#pragma unpacked

#elif defined(linux)
} __attribute__((packed, aligned(1))) udp_header_st;
#endif

typedef struct
{
	udp_header_st* header;
	void* data;
	uint32 length;
} udp_datagram_st;

udp_datagram_st* peek_udp_datagram(buffer_st* buffer, udp_datagram_st* udp);
void print_udp_header(udp_header_st* header);

#endif
