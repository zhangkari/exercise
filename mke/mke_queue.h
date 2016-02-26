#ifndef __MKE__QUEUE__H__
#define __MKE__QUEUE__H__

typedef struct mke_queue_s mke_queue_t;
struct mke_queue_s
{
	mke_queue_t *prev;
	mke_queue_t *next;
};

#define mke_queue_init(q)									\
	(q)->prev = q;											\
	(q)->next = q

#define mke_queue_empty(h)									\
	(h == (h)->prev)

#define mke_queue_insert_head(h, x)							\
	(x)->next = (h)->next; 									\
	(x)->next->prev = x; 									\
	(x)->prev = h; 											\
	(h)->next = x

#define mke_queue_insert_tail(h, x)							\
	(x)->next = h;											\
	(x)->prev = (h)->prev;									\
	(h)->prev->next = x;									\
	(h)->prev = x;					

#define mke_queue_head(h)									\
	(h)->next

#define mke_queue_last(h)									\
	(h)->prev

#define mke_queue_remove(x)									\
	(x)->next->prev = (x)->prev;							\
	(x)->prev->next = (x)->next;

mke_queue_t* mke_queue_middle(mke_queue_t *queue);
void mke_queue_sort(mke_queue_t *queue,
		int (*cmp)(const mke_queue_t *, const mke_queue_t *) );
#endif
