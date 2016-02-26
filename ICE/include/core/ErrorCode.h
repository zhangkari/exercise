#ifndef __ERRORCODE__H__
#define __ERRORCODE__H__

#include "IceType.h"

#ifndef NOERROR
#define NOERROR 0x00000000
#endif

#ifndef E_NOT_IMPLEMENTED
#define E_NOT_IMPLEMENTED 0x00000001
#endif

#ifndef E_FAILED_NEW_OBJECT
#define E_FAILED_NEW_OBJECT 0x00000002
#endif

#ifndef E_NULL_POINTER
#define E_NULL_POINTER 0x00000003
#endif

#ifndef E_INTERNAL_ERROR
#define E_INTERNAL_ERROR 0x00000004
#endif

static const char* GetErrorMessage(ECode code)
{
	switch(code)
	{
		case 0x00000000:
			return "No Error";
		case 0x00000001:	
			return "Not Implemented";
		case 0x00000002:
			return "Failed New Object";
		case 0x00000003:
			return "Null Pointer";
		case 0x00000004:
			return "Internal Error";
	}
}

#endif
