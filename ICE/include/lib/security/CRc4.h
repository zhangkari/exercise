
#ifndef __CRC4__H__
#define __CRC4__H__

#include <IUnknow.h>
#include <IceType.h>
#include <IRc4.h>

class CRc4: virtual public IRc4
{
	public:
		 void AddRef(){};
		 void ReleaseRef(){};
		 ECode QueryInterface(IID iid, void**);		
		 ECode Encrypt(char* key, char* input, char* result) ;
		 ECode Decrypt(char* key, char* input, char* result) ;
};

#endif

