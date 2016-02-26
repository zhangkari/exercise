/*******************************
 * file name:   linklist.h
 * description: linklist API 
 * date:        2015-01-19
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#ifndef __LINKLIST__H__
#define __LINKLIST__H__

typedef struct linklist_s linklist_s;
typedef struct linklist_s linklist_t;

struct linklist_s
{
    void        *elem;
    linklist_s  *next;
};

typedef int (*cb_compare)(void *, void *);


/**
 * init linklist
 */
linklist_s* init_linklist();

/**
 * add node in list
 */
int add_list_elem(linklist_s *list, void *elem);

/**
 * remove node from list
 */
int remove_list_elem(linklist_s *list, void *elem, cb_compare);

/**
 * free linklist
 */
void free_linklist(linklist_s *list);

#endif
