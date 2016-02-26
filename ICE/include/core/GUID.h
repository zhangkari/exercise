#ifndef __GUID__H__
#define __GUID__H__

typedef struct GUID
{
	char reserve[2];
	char macaddr[6];
	char seconds[8];
	char usecond[8];
}GUID;

#endif
