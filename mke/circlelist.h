#ifndef __CIRCLE__LIST__
#define __CIRCLE__LIST__

#include <assert.h>

typedef struct circlelist circlelist;

struct circlelist
{
    circlelist* next;
    circlelist* prev;
};

static inline void clist_init_head(circlelist *head)         
{
    assert (NULL != head);                             
    head->next = head;                               
    head->prev = head;       
}

static inline void _clist_add(circlelist *new,
        circlelist *prev,
        circlelist *next) 
{
    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
}

static inline void clist_add(circlelist *head, circlelist *node)      
{
    assert (NULL != head && NULL != node);              
    _clist_add(node, head, head->next);
}

static inline void clist_add_tail(circlelist *head, circlelist *node) 
{
    assert (NULL != head && NULL != node);              
    _clist_add(node, head->prev, head);
}

static inline void clist_remove(circlelist *node)        
{
    assert (NULL != node);                              
    node->prev->next = node->next;                  
    node->next->prev = node->prev;                  
}

static inline int clist_is_empty(const circlelist *head)
{
    return head->next == head;
}

static inline int clist_is_last(const circlelist *list,
                const circlelist *head)
{
    return list->next == head;
}

#define clist_for_each(list, head) \
    for (list = (head)->next; list != head; list = list->next)

#define clist_for_each_prev(list, head) \
    for (list = (head)->prev; list != head; list = list->prev)

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *) 0)->MEMBER)

#define container_of(ptr, type, member) ({ \
        const typeof( ((type *) 0)->member) *_mptr = (ptr); \
        (type *)( (char *)_mptr - offsetof(type, member) ); })

#define clist_entry(ptr, type, member) \
    container_of(ptr, type, member)

#endif
