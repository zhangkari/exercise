
#ifndef __IUNKNOW__H__
#define __IUNKNOW__H__
#include "IceType.h"
class IUnknow
{
	public:
		virtual	ECode QueryInterface(IID iid, void** ppv) = 0;
		virtual	void AddRef() = 0;
		virtual	void ReleaseRef() = 0;
};
#endif
