/*************************************
 * filename:	nictrl.c
 * describe:	net interface control
 *
 *************************************/
#include "type.h"
#include "nictrl.h"
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>

bool SetPromisc(const char* ifname, bool flag)
{
	int f, s;
	struct ifreq ifr;
	if ( (f = socket(AF_INET, SOCK_PACKET, htons(ETH_P_IP) ) ) < 0) {
		printf("Failed create socket, %s\n", strerror(errno));
		return false;
	}	

	strcpy(ifr.ifr_name, ifname);
	if ( (s = ioctl(f, SIOCGIFFLAGS, &ifr) ) < 0) {
		printf("Failed ioctl socket, %s\n", strerror(errno));
		close(f);
		return false;
	}

	if (flag) {
		ifr.ifr_flags |= IFF_PROMISC;
	}
	else {
		ifr.ifr_flags &= ~IFF_PROMISC;
	}

	if ( (s = ioctl(f, SIOCSIFFLAGS, &ifr) ) < 0) {
		printf("Failed ioctl socket, %s\n", strerror(errno));
		close(f);
		return false;
	}

	return true;
}

bool GetRawSocket(int layer, int* socketfd)
{
	if (layer == LAYER_NETWORK) {
		*socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	}
	else if (layer == LAYER_DATA_LINK) {
		*socketfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
	}

	if (*socketfd < 0) {
		printf("Failed GetRawSocket,%s\n", strerror(errno));
		return false;
	}
	
	return true;
}
