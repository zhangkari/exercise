#include <MacAddr.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <ErrorCode.h>

ECode getMacAddr(char* addr, int* len)
{
	if(addr == NULL)
	{
		printf("Illegal argument,NULL pointer\n");
		return E_NULL_POINTER;
	}

	const char* device = "eth0";
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	struct ifreq req;
	int err;
	strcpy(req.ifr_name, device);
	err = ioctl(s, SIOCGIFHWADDR, &req);
	close(s);
	if(err < 0)
	{
		printf("Failed get mac addr,%s\n", strerror(errno));
		return E_INTERNAL_ERROR;
	}

	memcpy(addr, req.ifr_hwaddr.sa_data, ETH_ALEN);
	if(NULL != len)
	{
		*len = ETH_ALEN;
	}

	printf("ETH_ALEN:%d\n", ETH_ALEN);
	return NOERROR;
}
