#ifndef __IP__PACKET__H__
#define __IP__PACKET__H__

#include "type.h"
#include "mac_frame.h"
#include "byteorder.h"

#ifndef PROTO_ICMP
#define PROTO_ICMP 1
#endif

#ifndef PROTO_IGMP
#define PROTO_IGMP 2
#endif

// IP in IP  (encapsulation)
#ifndef PROTO_IP
#define PROTO_IP 4
#endif

#ifndef PROTO_TCP
#define PROTO_TCP 6
#endif

#ifndef PROTO_UDP
#define PROTO_UDP 17
#endif

#ifdef _WIN32
#pragma packed 1
#endif
typedef struct
{
#if defined(__LITTLE__ENDIAN__)
	uint8     headlen : 4;
	uint8     version : 4;
#elif defined(__BIG__ENDIAN__)
	uint8     version : 4;
	uint8     headlen : 4;
#else
#error "Errors in byteorder.h, no endian defined"
#endif
	uint8     tos;
	uint16    total;
	uint16    id;
	uint16    offset;
	uint8     ttl;
	uint8     protocol;
	uint16    checksum;
	uint32    srcaddr;
	uint32    dstaddr;
#if defined(_WIN32)
} ip_header_st;
#pragma unpack

#elif defined(linux)
} __attribute__((packed, aligned(1))) ip_header_st;
#endif

typedef struct
{
	ip_header_st* header;
	void* data;
	uint32 length;
} ip_packet_st;

ip_packet_st* peek_ip_packet(buffer_st* buffer, ip_packet_st* ip);
void print_ip_header(ip_header_st* header);

#endif
