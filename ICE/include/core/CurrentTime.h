#ifndef __CURRENTTIME__H__
#define __CURRENTTIME__H__

#include <IceType.h>

ECode getCurSecond(ulong* sec);

ECode getCurAccurateTime(ulong* sec, ulong* usec);

#endif

