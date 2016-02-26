#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <protocol.h>
#include <comm.h>
#include <config.h>
#include <mdcntxt.h>

void main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage %s token\n", argv[0]);
        return;
    }

    int token = 0;
    token = atoi(argv[1]);
    token = htonl(token);
	mdcntxt_t *cntxt = default_master_cntxt(token);
	if (NULL == cntxt) {
		free_mdcntxt(cntxt);
		return;
	}

	if (md_start(cntxt) < 0) {
		Log("master devcie start failed\n");
		free_mdcntxt(cntxt);
		return;
	}

	free_mdcntxt(cntxt);
}
