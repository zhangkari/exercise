#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "circlelist.h"
#include "mke_log.h"
#include "mke_thrdpool.h"

typedef struct
{
    circlelist list;
    int data;
} Block;

static void signal_handler(int signum);
static void* user_task(void *param);
static void* test_thread_func(void *param);
static void test_log();
volatile static int exit_flag = 0;

int nFlag = 1;

#define TAG "main"

#define TEST_LOG
#define TEST_CIRCLELIST

int main()
{
    (void) signal(SIGINT, signal_handler);

#ifdef TEST_LOG
    turn_log_on();
    test_log();
#endif

#ifdef TEST_THRDPOOL
    pthread_t pid = 0;
    thrdpool_context_t *context = NULL;
    context = thrdpool_start(20);
    if (NULL != context) {
        if (pthread_create(&pid, NULL, test_thread_func, context) ) {
            exit_flag = 1;
        }

        while(!exit_flag) {
        }
    }
    (void) thrdpool_stop(context);
#endif

#ifdef TEST_CIRCLELIST
    circlelist head;
    Block b1, b2, b3, b4;
    b1.data = 100;
    b2.data = 200;
    b3.data = 300;
    b4.data = 400;

    clist_init_head(&head);
    clist_add_tail(&head, &b1.list);
    clist_add_tail(&head, &b2.list);
    clist_add_tail(&head, &b3.list);
    clist_add_tail(&head, &b4.list);

    circlelist *plist;
    clist_for_each(plist, &head) {
        Block *b = clist_entry(plist, Block, list);
        printf("data=%d\n", b->data);

        Block *bp = clist_entry(plist->prev, Block, list);
        if (&bp->list == &head) {
            bp = clist_entry(head.prev, Block, list);
        }
        printf("prev data=%d\n", bp->data);

        Block *bn = clist_entry(plist->next, Block, list);
        if (&bn->list == &head) {
            bn = clist_entry(head.next, Block, list);
        }
        printf("next data=%d\n", bn->data);
    }
#endif

    while (nFlag) { }

    return 0;
}

static void signal_handler(int signum)
{
    if (SIGINT == signum) {
        printf("catch SIGINT and exit...\n");
        exit_flag = 1;
        turn_log_off();
        nFlag = 0;
    }

    return ;
}

static void test_log()
{
    char log[256];
    sprintf(log, "test logd value=%d\n", 100);
    log_d(TAG, log);

    log_e("main", "leaveing test_log()");
}

void* user_task(void *param)
{
    long i = (long)param;
    printf("task %ld\n", i);
    return 0;
}

void* test_thread_func(void *param)
{
    thrdpool_context_t *context = (thrdpool_context_t *)param;
    thrdpool_job_t job1 = {
        .task     = user_task,
        .param 	  = (void *)(0),
        .priority = 0,
        .next     = NULL
    }; 

    thrdpool_job_t job2 = {
        .task     = user_task,
        .param 	  = (void *)(1),
        .priority = 1,
        .next     = NULL
    };

    thrdpool_job_t job3 = {
        .task     = user_task,
        .param 	  = (void *)(2),
        .priority = 1,
        .next     = NULL

    };

    long i;
    for (i=0; i<100; ++i) {
        (void) thrdpool_join(context, &job1);
        (void) thrdpool_join(context, &job2);
        (void) thrdpool_join(context, &job3);

        (void) sleep(2);
    }

    return 0;
}
