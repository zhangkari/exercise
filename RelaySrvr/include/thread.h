/*******************************
 * file name:   thread.h
 * description: define common thread 
 * date:        2015-01-19
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#ifndef __THREAD__H__
#define __THREAD__H__

#include <comm.h>

#ifdef linux
typedef void* (*threadfunc)(void *);
#endif

#ifdef WIN32
typedef void* (*threadfunc)(void *);
#endif

int32 create_thread(threadfunc func, void *param);
int32 destroy_thread(int32 tid);

#endif
