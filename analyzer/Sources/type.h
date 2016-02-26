/*************************************
 * filename:	type.h
 * describe:	define portable type
 *
 *************************************/

#ifndef __TYPE__H__
#define __TYPE__H__

typedef char  int8;
typedef short int16;
typedef int   int32;
typedef unsigned char  bool;
typedef unsigned char  uint8;
typedef unsigned int   uint32;
typedef unsigned short uint16;

#ifndef true
#define true 0xff
#endif

#ifndef false
#define false 0x00 
#endif


#endif
