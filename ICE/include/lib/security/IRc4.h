
#ifndef __IRC4__H__
#define __IRC4__H__

#include <IUnknow.h>
#include <IceType.h>

class IRc4: virtual public IUnknow
{
	public:
		virtual ECode Encrypt(char* key, char* input, char* result) = 0;
		virtual ECode Decrypt(char* key, char* input, char* result) = 0;
};

#endif

