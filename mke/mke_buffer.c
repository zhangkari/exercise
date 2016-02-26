/********************************
 * file:        mke_buffer.c
 * description: impl buffer
 * author:      kari.zhang
 * date:        2014-09-03
 *
 * history:
 *
 *********************************/
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mke_buffer.h"

buffer_t* alloc_buffer(int size)
{
    if (size <= 0) {
        return NULL;
    }
    
    buffer_t *buf = (buffer_t *)calloc(1, sizeof(*buf) );
    if (NULL == buf) {
        return NULL;
    }
    buf->data = (char *)malloc(size);
    if (NULL == buf->data) {
        free(buf);
        return NULL;
    }
    buf->size = size;

    return buf;
}

buffer_t* init_buffer(const char *data)
{
    if (NULL == data) {
        return NULL;
    }

    int len = strlen(data);
    buffer_t *buf = alloc_buffer(len);
    if (NULL == buf) {
        return NULL;
    }
    strncpy(buf->data, data, len);
    buf->len = len;

    return buf;
}

int append_buffer(buffer_t *buf, const char *data)
{
    if (NULL == buf || NULL ==  data) {
        return -1;
    }

    int len = strlen(data);
    if (buf->len + len > buf->size) {
        buf->data = (char *)realloc(buf->data, buf->len + len);
        if (NULL == buf->data) {
            return -1;
        }
        buf->size = buf->len + len;
    }

    strncpy(buf->data + buf->len, data, len);
    buf->len += len;

    return 0;
}

int free_buffer(buffer_t *buf)
{
    if (NULL != buf) {
        if (NULL != buf->data) {
            free(buf->data);
            buf->data = NULL;
        }
        free(buf);
        buf = NULL;
    }

    return 0;
}
