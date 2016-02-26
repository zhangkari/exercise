#include <CurrentTime.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <ErrorCode.h>

ECode getCurSecond(ulong* now)
{
	if(NULL == now)
		return E_NULL_POINTER;
	time((time_t*)now);
	return NOERROR;
}

ECode getCurAccurateTime(ulong* sec, ulong* usec)
{
	if(NULL == sec || NULL == usec)
		return E_NULL_POINTER;
	struct timeval now;
	gettimeofday(&now, 0);
	*sec =  now.tv_sec;
	*usec = now.tv_usec;
	return NOERROR;
}

