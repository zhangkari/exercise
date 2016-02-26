/******************************
 * file:        mke_log.c
 * description: impl log utility
 * author:      kari.zhang
 * date:        2014-09-03
 *
 * history:
 *
 * ****************************/

#include <pthread.h>
#include <stdlib.h>

#include "mke_buffer.h"
#include "mke_log.h"

typedef struct loglist_s loglist_t;
struct loglist_s
{
    buffer_t  *tag;
    buffer_t  *log;
    loglist_t *next;
};

typedef void (* log_hook_t)(const char *tag, const char *log);

typedef struct hook_list_s hook_list_t;
struct hook_list_s {
    log_hook_t   hook_func;
    hook_list_t  *next;
};

struct log_handle_s
{
    char             sw;        // take on or off the log
    pthread_mutex_t  lock;      // Lock use to synchronize
    hook_list_t      *log_hook; // Head of hook list
    loglist_t        *vlogs;    // Verbose log list
    loglist_t        *dlogs;    // Debug log list
    loglist_t        *wlogs;    // Warning log list
    loglist_t        *elogs;    // Error log list
    FILE             *fp;       // output log
};

typedef struct log_handle_s log_handle_t;

log_handle_t *g_loghnd = NULL;

static loglist_t* print_loglist(loglist_t *list, char c) {
    loglist_t *head = list;
    loglist_t *node = NULL;

    pthread_mutex_lock(&g_loghnd->lock);
    hook_list_t *hook = g_loghnd->log_hook;
    while (NULL != head) {
        node = head;
        fprintf(g_loghnd->fp, "%c/%s: %s\n", c, node->tag->data, node->log->data);
        while (NULL != hook) {
            hook->hook_func(node->tag->data, node->log->data);
            hook = hook->next;
        }
        head = head->next;
        free_buffer(node->tag);
        free_buffer(node->log);
        free(node);
        node = NULL;
    }
    pthread_mutex_unlock(&g_loghnd->lock);

    return head;
}

void* log_thread_func(void *param) {
    while (g_loghnd->sw) {
        g_loghnd->elogs = print_loglist(g_loghnd->elogs, 'E');
        g_loghnd->wlogs = print_loglist(g_loghnd->wlogs, 'W');
        g_loghnd->dlogs = print_loglist(g_loghnd->dlogs, 'D');
        g_loghnd->vlogs = print_loglist(g_loghnd->vlogs, 'V');
    }
}

int turn_log_on()
{
    if (NULL == g_loghnd) {
        g_loghnd = (log_handle_t *)calloc(1, sizeof(*g_loghnd) );
        if (NULL == g_loghnd) {
            return -1;
        }

        do {
            if (pthread_mutex_init(&g_loghnd->lock, NULL)) {
                break;
            }

            g_loghnd->fp = stderr;
            g_loghnd->sw = 1;

            pthread_t pid;
            if (pthread_create(&pid, NULL, log_thread_func, NULL) ) {
                break;
            }

            return 0;
        }while (0);

        return -1;
    }
    else {
        g_loghnd->sw = 1;
    }
}

int turn_log_off()
{
    if (NULL != g_loghnd) {
        g_loghnd->sw = 0;
    }

    return 0;
}

static int add_log(const char *tag, const char *log, char level) {
    if (NULL == tag || NULL == log) {
        return -1;
    }

    loglist_t *node = NULL;
    node = (loglist_t *)calloc(1, sizeof(loglist_t));
    if (NULL == node) {
        return -1;
    }
    node->tag  = init_buffer(tag);
    node->log  = init_buffer(log);
    node->next = NULL;

    loglist_t **loghead = NULL;
    switch (level) {
        case 'D':
            loghead = &g_loghnd->dlogs;
            break;

        case 'W':
            loghead = &g_loghnd->wlogs;
            break;

        case 'V':
            loghead = &g_loghnd->vlogs;
            break;

        case 'E':
            loghead = &g_loghnd->elogs;
            break;

        default:
            printf("Invalid log level.\n");
            return -1;
    }

    if (NULL == *loghead) {
        pthread_mutex_lock(&g_loghnd->lock);
        *loghead = node;
        pthread_mutex_unlock(&g_loghnd->lock);
    }
    else {
        loglist_t *temp = *loghead;
        while (NULL != temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }

    return 0;
}

int log_v(const char *tag, const char *log)
{
    return add_log(tag, log, 'V');
}

int log_d(const char *tag, const char *log)
{
    return add_log(tag, log, 'D');
}

int log_w(const char *tag, const char *log)
{
    return add_log(tag, log, 'W');
}

int log_e(const char *tag, const char *log)
{
    return add_log(tag, log, 'E');
}

int set_log_output(FILE *fp)
{
    if (NULL == fp) {
        return -1;
    }

    if (NULL != g_loghnd) {
        g_loghnd->fp = fp;
    }

    return 0;
}
