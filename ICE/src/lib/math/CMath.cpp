#include "IID.h"
#include "CMath.h"

int CMath::Add(int op1, int op2)
{
	return op1 + op2;
}

int CMath::Pow(int a, int e)
{
	int ret = 1;
	while(e--)
	{

		ret *= a;
	}
	return ret;
}

void CMath::AddRef()
{
	++mRef;
}

void CMath::ReleaseRef()
{
	--mRef;
	if(0 == mRef)
	{
		delete this;
	}
}

ECode CMath::QueryInterface(IID gid, void**ppv)
{
	if(gid == IID_ISimpleMath)
	{
		*ppv = static_cast<ISimpleMath*>(this);
		return 0;
	}

	if(gid == IID_IAdvanceMath)
	{
		*ppv = static_cast<IAdvMath*>(this);
		return 0;

	}

	*ppv = 0;
	return -1;
}
