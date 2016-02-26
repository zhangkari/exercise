#include "nictrl.h"
#include "mac_frame.h"
#include "ip_packet.h"
#include "udp_datagram.h"
#include "tcp_message.h"
#include "http_message.h"
#include "log.h"

#include <stdio.h>
#include <time.h>

#ifdef linux
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

int main(int argc, char** argv)
{
	char* devname = NULL;
	if (1 == argc) {
		devname = "eth0";
	}
	else {
		devname = argv[1];
	}

	int rawSocket;

#ifdef linux
	if (!SetPromisc(devname, true)) {
		return -1;
	}

	if (!GetRawSocket(LAYER_DATA_LINK, &rawSocket)) {
		SetPromisc("eth0", false);
		return -1;
	}
#endif

#ifdef _WIN32
	if (!GetRawSocket(LAYER_DATA_LINK, &rawSocket)) {
		return -1;
	}
#endif

	buffer_st *buffer = alloc_buffer(MAX_MAC_FRAME_SIZE);
	if (NULL == buffer) {
		return -1;
	}

	int nRead, nWrite;

	mac_frame_st*    macframe    = NULL;
	mac_header_st*   macheader   = NULL;
	ip_packet_st*    ippacket    = NULL;
	udp_datagram_st* udpdatagram = NULL;
	tcp_message_st*  tcpmessage  = NULL;
	http_message_st* httpmessage = NULL;


	bool result = false;
	time_t t_start;
	time(&t_start);
	// run 10 minutes
	while (time(NULL) < t_start + 10 * 60) {
		nRead = recvfrom(
				rawSocket, 
				buffer->base, 
				MAX_MAC_FRAME_SIZE, 
				0, 
				NULL, 
				NULL);
		buffer->length = nRead;


		macframe = peek_mac_frame(buffer, macframe);
		if (NULL == macframe) {
			continue;	
		}

		//	print_mac_header(macframe->header);

		ippacket = peek_ip_packet(buffer, ippacket); 
		if (NULL == ippacket) {
			continue;
		}

		//  print_ip_header(ippacket->header);

		if (PROTO_UDP == ippacket->header->protocol) {
			udpdatagram = peek_udp_datagram(buffer, udpdatagram);
			if (NULL == udpdatagram) {
				continue;
			}
			//	print_udp_header(udpdatagram->header);
		}
		else if (PROTO_TCP == ippacket->header->protocol) {
			tcpmessage = peek_tcp_message(buffer, tcpmessage);
			if (NULL == tcpmessage) {
				continue;
			}
			//	print_tcp_header(tcpmessage->header);

			httpmessage = peek_http_message(buffer, httpmessage);
			if (NULL == httpmessage) {
				continue;
			}

			print_http_message(httpmessage);
		}
	}	

#ifdef linux	
	SetPromisc(devname, false);
#endif
	free_buffer(buffer);

	return 0;
} 
