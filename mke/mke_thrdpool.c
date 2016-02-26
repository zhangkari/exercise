#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "mke_thrdpool.h"
#include "mke_type.h"

#define ERROR "ERROR:"
#define INFO  "INFO:"

typedef struct thrdpool_job_queue_t 
{
	pthread_mutex_t mutex; 	// lock for cond
	pthread_cond_t  cond;	// synchronize threads
	uint32_t length;		// length of the queue
	thrdpool_job_t *head;	// head of the queue
	thrdpool_job_t *tail;	// tail of the queue
} thrdpool_job_queue_t;

typedef struct thrdpool_context_t 
{
	pthread_mutex_t mutex; 		// lock for cond
	pthread_cond_t  cond;		// synchronize threads
	thrdpool_job_queue_t *hiq;	// high priority queue
	thrdpool_job_queue_t *noq;	// normal priority queue
	thrdpool_job_queue_t *loq;	// low priority queue
	uint32_t max_num;			// max threads
	uint32_t curr_num;			// current threads
	uint32_t idle_num;			// idle threads
	uint8_t  exit_flag;			// indicate if exit
} thrdpool_context_t;

int static init_mutex_and_cond(pthread_mutex_t *mutex, pthread_cond_t *cond)
{
	if (NULL == mutex || pthread_mutex_init(mutex, NULL) ) {
		return E_INIT_MUTEX;
	}

	if (NULL == cond || pthread_cond_init(cond, NULL) ) {
		return E_INIT_COND;
	}

	return NOERROR;
}

static int init_job_queue(thrdpool_job_queue_t **queue)
{
	*queue = (thrdpool_job_queue_t *)calloc(1, sizeof(**queue) );
	if (NULL == *queue ||
			init_mutex_and_cond(&(*queue)->mutex, &(*queue)->cond) ) {
		return E_INIT_FAILED;
	}

	return NOERROR;
}

static void destroy_job_queue(thrdpool_job_queue_t *queue)
{
	if (NULL != queue) {
		pthread_mutex_destroy(&queue->mutex);
		pthread_cond_destroy(&queue->cond);
		free(queue);
		queue = NULL;
	}

	return;
}

static thrdpool_context_t* thrdpool_init(int max)
{
	thrdpool_context_t *context = NULL;

	do {
		context = (thrdpool_context_t *)calloc(1, sizeof(*context) );
		if (NULL == context ||
				init_mutex_and_cond(&context->mutex, &context->cond) ){
			printf(ERROR "Failed calloc thrdpool_context_t.\n");
			break;
		}

		if (init_job_queue(&context->hiq) ||
				init_job_queue(&context->noq) ||
				init_job_queue(&context->loq) ) {	
			break;
		}

		context->max_num = max;
		return context;

	} while(0);

	if (NULL != context) {
		free(context);
		context = NULL;
	}

	destroy_job_queue(context->hiq);
	destroy_job_queue(context->noq);
	destroy_job_queue(context->loq);

	return NULL;
}

static void process_job_queue(thrdpool_job_queue_t *queue)
{
	thrdpool_job_t *job = NULL;

	while (queue && queue->head) {
		(void) pthread_mutex_lock(&queue->mutex); {
			--queue->length;
			job = queue->head;
			queue->head = job->next;
			if (NULL == queue->head) {
				queue->tail = NULL;
			}
		}
		(void) pthread_mutex_unlock(&queue->mutex);

		if (job) {
			(void) job->task(job->param);
		}
	}

	return;
}

static void* worker_thread_func(void *param)
{
	thrdpool_context_t *context = (thrdpool_context_t *)param;
	while (!context->exit_flag) {
		(void) pthread_mutex_lock(&context->mutex);
		while (NULL == context->hiq->head &&
				NULL == context->noq->head &&
				NULL == context->loq->head ) {
			(void) pthread_cond_wait(&context->cond, &context->mutex);
		}
		(void) pthread_mutex_unlock(&context->mutex);

		(void) process_job_queue(context->hiq);
		(void) process_job_queue(context->noq);
		(void) process_job_queue(context->loq);
	}

	return 0;
}

static int prepare_worker_threads(thrdpool_context_t *context)
{
	uint32_t i = 0;
	pthread_t pid = 0;

	if (NULL != context) {
		for (i=0; i<context->curr_num; ++i) {
			if (pthread_create(&pid, NULL, worker_thread_func, context) ) {
				printf(ERROR "Failed create thread at %d \n", i);
				return E_CREATE_THREAD;
			}
			printf(INFO "Success create thread id=%lx\n", pid);
		}
	}

	return NOERROR;
}

thrdpool_context_t* thrdpool_start(int max)
{
	thrdpool_context_t *context = NULL;

	if (max < 0 || max > 65535) {
		printf(ERROR "Invalid max value\n");
		return NULL;
	}

	context = thrdpool_init(max);
	if (NULL != context) {
		context->curr_num  = 4;
		context->idle_num = 4;
		(void) prepare_worker_threads(context);
	}

	return context;
}

static int join_job_queue(thrdpool_job_queue_t *queue, thrdpool_job_t *job)
{
	if (NULL == queue || NULL == job) {
		return E_INVALID_ARGUMENT;
	}

	//
	// should add a function named createJob(user_task *task, param ...)
	// job->next = NULL;
	//

	(void) pthread_mutex_lock(&queue->mutex); {
		++queue->length;
		if (queue->tail) {
			queue->tail->next = job;
			queue->tail = job;
		}
		else {
			queue->head = job;
			queue->tail = job;
		}
	}
	(void) pthread_mutex_unlock(&queue->mutex);

	return NOERROR;
}

int thrdpool_join(thrdpool_context_t *context, thrdpool_job_t *job)
{
	int ret = E_INVALID_ARGUMENT;

	if (job) {
		switch (job->priority) {
			case  PRI_HIGH:
				ret = join_job_queue(context->hiq, job);
				break;

			case PRI_NORMAL:
				ret = join_job_queue(context->noq, job);
				break;

			case PRI_LOW:
				ret = join_job_queue(context->loq, job);
				break;

			default:
				printf(ERROR "Invalid priority value\n");
		}
	}

	if (NOERROR == ret) {
		(void) pthread_mutex_lock(&context->mutex);
		(void) pthread_cond_broadcast(&context->cond);
		(void) pthread_mutex_unlock(&context->mutex);
	}

	return ret;
}

int thrdpool_stop(thrdpool_context_t *context)
{
	context->exit_flag = 1;
	destroy_job_queue(context->hiq);
	destroy_job_queue(context->noq);
	destroy_job_queue(context->loq);

	if (context) {
		free(context);
		context = NULL;
	}

	return 0;
}

