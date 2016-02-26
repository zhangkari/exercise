/********************************
 * file:        mke_buffer.h
 * description: define buffer api
 * author:      kari.zhang
 * date:        2014-09-03
 *
 * history:
 *
 *********************************/

#ifndef __MKE__BUFFER__H__
#define __MKE__BUFFER__H__
    
struct buffer_s
{
    unsigned int size;      // the max-size of the buffer in bytes
    unsigned int len;       // the used size of the buffer in bytes
    char *data;             // the address of the data
};

typedef struct buffer_s  buffer_t;

buffer_t* alloc_buffer(int size);
buffer_t* init_buffer(const char *data);
int append_buffer(buffer_t *buf, const char *data);
int free_buffer(buffer_t *buf);

#endif
