/*******************************
 * file name:   utility.h
 * description: declare APIs
 * date:        2015-01-15
 * author:      kari.zhang
 *
 * modifications:
 *
 * ****************************/

#ifndef __UTILITY__H__
#define __UTILITY__H__

/*
 * format ip to string
 * param:
		ip: 
		buff: 
   return:
		success:	buff
		failed:		NULL
 */
char* format_ip(uint32 ip, char* buff);

#endif
