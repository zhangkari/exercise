/**********************************************
 * file name:	buffer.h
 * description: sample memory buffer
 *
 *********************************************/

//
// remvoe the macro below may case issues when include<stdio.h>
//

#if (defined __USE_XOPEN || defined __USE_XOPEN2K8)
#undef __USE_XOPEN
#undef __USE_XOPEN2K8
#endif 


#if (defined __USE_XOPEN || defined __USE_XOPEN2K8)
#undef __USE_XOPEN
#undef __USE_XOPEN2K8
#endif

#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"
#include "log.h"

bool init_buffer(buffer_st* buff)
{
	if (NULL == buff) {
		Log(stdout, "NULL pointer Exception %s:%d\n", __FILE__, __LINE__);
		return false;
	}
	if (buff->length <= 0) {
		Log(stdout, "Buffer length Exception %d %s:%d\n", buff->length, __FILE__, __LINE__);
		return false;
	}

	buff->base = (char*)malloc(buff->length);
	if (NULL == buff->base) {
		Log(stdout, "Failed malloc memory %s:%d\n", __FILE__, __LINE__);
		return false;
	}

	return true;
}

buffer_st* alloc_buffer(uint32 size)
{
	if (size <= 0) {
		Log(stdout, "Buffer length Exception %d %s:%d\n", size, __FILE__, __LINE__);
		return NULL;
	}

	buffer_st *buffer = (buffer_st*)malloc(sizeof(buffer_st));
	if (NULL == buffer) {
		Log(stdout, "Failed malloc memory %s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

	buffer->length = size;

	if (init_buffer(buffer)) {
		return buffer;
	}
	else {
		return NULL;
	}
}

bool free_buffer(buffer_st* buffer)
{
	if (NULL != buffer) {
		if (NULL != buffer->base) {
			free(buffer->base);
			buffer->base = NULL;
		}
		free(buffer);
		buffer = NULL;
	}

	return true;
}
