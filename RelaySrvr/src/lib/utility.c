/*******************************
 * file name:   utility.c
 * description: utils for monitor 
 * date:        2015-01-15
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <buffer.h>
#include <comm.h>
#include <utility.h>

/*
 * format ip to string
 * param:
		ip: 
		buff: 
   return:
		success:	buff
		failed:		NULL
 */
char* format_ip(uint32 ip, char* buff)
{
	if (NULL == buff) {
		return NULL;
	}
    sprintf(buff, "%d.%d.%d.%d",
			ip & 0xff, 
            (ip>>8) & 0xff, 
            (ip>>16) & 0xff,
            (ip>>24) & 0xff);

	return buff;
}
