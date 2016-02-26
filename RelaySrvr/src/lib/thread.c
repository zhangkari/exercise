/*******************************
 * file name:   thread.c
 * description: wrap thread 
 * date:        2015-01-19
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#ifdef linux
#include <pthread.h>
#endif

#ifdef WIN32
#include <windows.h>
#endif

#include <thread.h>

int32 create_thread(threadfunc func, void *param)
{
#ifdef linux
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, func, param);
    if (ret) {
        LogE("Failed create_thread\n");
        return -1;
    }
    return 0;
#endif    

#ifdef WIN32
    int ret = _beginthread(func, 0, param);
    if (-1 == ret) {
        LogE("Failed create_thread\n");
        return -1;
    }
    return 0;

#endif

}

int32 destroy_thread(int32 tid)
{

}
