/**************************
 * file:    rscntxt.h
 * author:  Kari.Zhang
 * date:    2015-03-03
 *
 * ***********************/

#ifndef __RSCNTXT__H__
#define __RSCNTXT__H__

#define DEFAULT_BACKLOG 16
#define HEART_BEAT_CYCLE 2 * 1000

struct rscntxt_t;
typedef struct rscntxt_t rscntxt_t;

/**
 * Return the rscntxt_t by default value
 */
rscntxt_t* default_context();

/**
 * Return the rscntxt_t by the config file
 */
rscntxt_t* create_context(const char *path);

/**
 * Start relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int rs_start(rscntxt_t *cntxt);

/**
 * Poll relay server
 * Return:
 *      0  success
 *      -1 failed
 */
int rs_loop(rscntxt_t *cntxt);

/**
 * Free the context 
 */
void free_context(rscntxt_t *cntxt);

/**
 * dumplicate rscntxt
 */
void dump_context(rscntxt_t *cntxt);

#endif
