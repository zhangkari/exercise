/*******************************
 * file name:   linklist.c
 * description: utils for linklist 
 * date:        2015-01-19
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#include <stdlib.h>
#include <string.h>
#include <comm.h>
#include <linklist.h>

/**
 * init linklist
 */
linklist_s* init_linklist()
{
    linklist_s *list = (linklist_s *)calloc(sizeof(*list), 1);
    return list;
}

/**
 * add node in list
 */
int add_list_elem(linklist_s *list, void *elem)
{
    VALIDATE_NOT_NULL2(list, elem);
    if (NULL == list->elem) {
        list->elem = elem;
        return 0;
    }

    linklist_s *node = (linklist_s *)calloc(sizeof(*list), 1);
    if (NULL == node) {
        return -1;
    }
    node->elem  = elem;

    linklist_s *ll = list;
    while (NULL != ll->next) {
        ll = ll->next;
    }
    ll->next = node;

    return 0;
}

/**
 * remove node from list
 */
int remove_list_elem(linklist_s *list, void *elem, cb_compare cmp)
{
    VALIDATE_NOT_NULL2(list, elem);

    linklist_s *ll = list;
    linklist_s *temp = NULL;

    if (NULL == ll->next) {
        if (!cmp(elem, ll->elem)) {
            list->elem = NULL;
            return 0;
        }
    }

    while (NULL != ll->next) {
        if (!cmp(elem, ll->next->elem)) {
            temp = ll->next;
            ll->next = temp->next;
            free (temp);
            temp = NULL; 
            return 0;
        }
        ll == ll->next;
    }

    return -1;
}

/**
 * free linklist
 */
void free_linklist(linklist_s *list)
{
    linklist_s *ll = NULL;
    while (NULL != list) {
        ll = list;
        list = ll->next;
        free(ll);
    }
}
