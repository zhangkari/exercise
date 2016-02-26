#include <signal.h>
#include <comm.h>
#include <protocol.h>
#include <config.h>
#include <sdcntxt.h>

static int gRunFlag = 1;
static void sigfunc(int sig);

void main(int argc, char **argv)
{
	signal(SIGINT, sigfunc);

	sdcntxt_t* cntxt = default_slave_cntxt();
	if (NULL == cntxt) {
		return ;
	}

	if (sd_start(cntxt) < 0) {
		Log("Failed called sd_start\n");
		free_sdcntxt(cntxt);
		cntxt = NULL;
		return;
	}

	while (gRunFlag) {
		sd_loop(cntxt);
	}
	free_sdcntxt(cntxt);
}

static void sigfunc(int sig) {
	if (SIGINT == sig) {
		Log(" Slave Device exiting\n");
		gRunFlag = 0;
	}
}
