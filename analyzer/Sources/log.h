/*********************************
 * file name:	log.h
 * description:	log util
 * 
 *
 ********************************/

#ifndef __LOG__H__
#define __LOG__H__

#include <stdio.h>
#include <stdarg.h>

// In release version, Please remove it.
#define DEBUG 1

void static Log(FILE* fp, const char* format, ...)
{

#ifdef DEBUG
	char logBuffer[2048] = {0};
	char* buf = logBuffer;
	int pos = 0;

	va_list arglist;
	pos = sprintf(buf, " ");
	buf += pos;

	va_start(arglist, format);
	pos = vsprintf(buf, format, arglist);
	va_end(arglist);

	buf += pos;
	*buf++ = 0x0d;
	*buf++ = 0x0a;
	*buf++ = 0x00;

	printf("[%s]%s", "TAG", logBuffer);
#endif

}
#endif
