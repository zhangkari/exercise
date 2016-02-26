#include "IceType.h"
#include "ErrorCode.h"
#include "IceFactory.h"
#include "CLSID.h"
#include "CMath.h"
#include "CRc4.h"

ECode CreateInstance(CLSID clsid, IUnknow** ppv)
{
	if(CLSID_CMATH == clsid)
	{
		CMath* math = new CMath();
		if(NULL != math)
		{
			*ppv = math;
			return NOERROR;
		}
		return E_FAILED_NEW_OBJECT;
	}

	if(CLSID_CRc4 == clsid)
	{
		CRc4* rc4 = new CRc4();
		if(NULL != rc4)
		{
			*ppv = rc4;
			return NOERROR;
		}
		return E_FAILED_NEW_OBJECT;
	}

	return E_NOT_IMPLEMENTED;
}
