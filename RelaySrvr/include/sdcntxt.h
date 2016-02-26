/**************************
 * file:    sdcntxt.h
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/

#ifndef __SDCNTXT__H__
#define __SDCNTXT__H__

#define DEFAULT_BACKLOG 1
#define HEART_BEAT_CYCLE 2 * 1000

struct sdcntxt_t;
typedef struct sdcntxt_t sdcntxt_t;

/**
 * Return the sdcntxt_t by default value
 */
sdcntxt_t* default_slave_cntxt();

/**
 * Return the sdcntxt_t by the config file
 */
sdcntxt_t* create_slave_cntxt(const char *path);

/**
 * Start relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int sd_start(sdcntxt_t *cntxt);

/**
 * Poll relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int sd_loop(sdcntxt_t *cntxt);

/**
 * Free the context 
 */
void free_sdcntxt(sdcntxt_t *cntxt);

/**
 * dumplicate rscntxt
 */
void dump_sdcntxt(sdcntxt_t *cntxt);

#endif
