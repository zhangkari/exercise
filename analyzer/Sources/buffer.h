#ifndef __BUFFER__H__
#define __BUFFER__H__

#include "type.h"

typedef struct
{
	void   *base;
	uint32 length;
}buffer_st;

bool init_buffer(buffer_st* buff);
buffer_st* alloc_buffer(uint32 size);
bool free_buffer(buffer_st* buff);

#endif
