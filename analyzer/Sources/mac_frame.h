#ifndef __MAC__FRAME__H__
#define __MAC__FRAME__H__

#include "type.h"
#include "buffer.h"

#ifndef MAX_MAC_FRAME_SIZE
#define MAX_MAC_FRAME_SIZE 1514 // NIC driver has removed FCS
#endif

#ifndef MIN_MAC_FRAME_SIZE
#define MIN_MAC_FRAME_SIZE 60 // NIC driver has removed FCS
#endif

#ifndef TYPE_IP
#define TYPE_IP 0X800
#endif

#ifndef TYPE_ARP
#define TYPE_ARP 0x806
#endif

#ifdef _WIN32
#pragma packed 1
#endif
typedef struct
{
	uint8  dst_addr[6];
	uint8  src_addr[6];
	uint16 type;
	// char[] data
	// int32 FCS(frame check serail)
#if defined(_WIN32)
} mac_header_st;
#pragma unpack

#elif defined(linux)
} __attribute((packed, aligned(1))) mac_header_st;
#endif

typedef struct
{
  mac_header_st* header;
  void* data;
  uint16 length;
} mac_frame_st;

mac_frame_st* peek_mac_frame(buffer_st* buffer, mac_frame_st* frame);
void print_mac_header(mac_header_st* header);

#endif
