
#ifndef __ISIMPLEMATH__H__
#define __ISIMPLEMATH__H__

#include "IUnknow.h"

class ISimpleMath: virtual public IUnknow
{
	public:
		virtual int Add(int nOp1, int nOp2) = 0;
};

#endif


