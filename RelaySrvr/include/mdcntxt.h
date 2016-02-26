/**************************
 * file:    mdcntxt.h
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/

#ifndef __MDCNTXT__H__
#define __MDCNTXT__H__

#define DEFAULT_BACKLOG 1
#define HEART_BEAT_CYCLE 2 * 1000

struct mdcntxt_t;
typedef struct mdcntxt_t mdcntxt_t;

/**
 * Return the mdcntxt_t by default value
 */
mdcntxt_t* default_master_cntxt(int token);

/**
 * Return the mdcntxt_t by the config file
 */
mdcntxt_t* create_master_cntxt(const char *path);

/**
 * Start relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int md_start(mdcntxt_t *cntxt);

/**
 * Poll relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int md_loop(mdcntxt_t *cntxt);

/**
 * Free the context 
 */
void free_mdcntxt(mdcntxt_t *cntxt);

/**
 * dumplicate rscntxt
 */
void dump_mdcntxt(mdcntxt_t *cntxt);

#endif
