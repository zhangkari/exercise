
#ifndef __IADVMATH__H__
#define __IADVMATH__H__

#include "IUnknow.h"

class IAdvMath: virtual public IUnknow
{
	public:
		virtual int Pow(int e, int n) = 0;
};

#endif


