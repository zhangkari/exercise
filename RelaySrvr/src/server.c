/*******************************
 * file name:   main.c
 * description: program entry 
 * date:        2015-01-19
 * author:      kari.zhang
 *
 * modifications:
 *
 * 1. Modified by Kari.Zhang @ 2015-01-19
 *      rearchitect & redesign
 * ****************************/

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <comm.h>
#include <rscntxt.h>

static void sigfunc(int sig);

int gRunFlag = 1;
int main(int argc, char *argv[]) 
{
    signal(SIGINT, sigfunc);

    rscntxt_t *cntxt = default_context();
    if (NULL == cntxt) {
        LogE("Failed get default context");
        return -1;
    }

    if (rs_start(cntxt) < 0) {
        LogE("Failed called rs_start");
        free_context(cntxt);
        cntxt = NULL;
        return -1;
    }

    while (gRunFlag) {
        rs_loop(cntxt);
    }

    free_context(cntxt);

    return 0;
}

static void sigfunc(int sig)
{
    if (SIGINT == sig) {
        Log(" RelaySrvr exiting\n");
        gRunFlag = 0;
    }
}
