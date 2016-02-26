#ifndef __MKE_THRDPOOL__H__
#define __MKE_THRDPOOL__H__
#include <stdint.h>

typedef struct thrdpool_context_t thrdpool_context_t;

enum job_priority
{
	PRI_LOW = 0,
	PRI_NORMAL,
	PRI_HIGH	
};
typedef void* (*user_task_t)(void *param);
typedef struct thrdpool_job_t
{
	user_task_t task;
	void *param;
	int priority;
	struct thrdpool_job_t *next;
} thrdpool_job_t;

thrdpool_context_t* thrdpool_start(int max_thread);
int thrdpool_join(thrdpool_context_t *context, thrdpool_job_t *job);
int thrdpool_stop(thrdpool_context_t *context);

#endif

