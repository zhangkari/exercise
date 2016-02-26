#include <IUnknow.h>
#include <IceType.h>
#include <string.h>
#include <CRc4.h>
#include <IID.h>
#include <ErrorCode.h>

ECode CRc4::QueryInterface(IID gid, void** ppv)
{
	if(gid == IID_IRc4Encrypt)
	{
		*ppv = static_cast<IRc4*>(this);
		return NOERROR;
	}

	if(gid == IID_IRc4Decrypt)
	{
		*ppv = static_cast<IRc4*>(this);
		return NOERROR;
	}

}

inline static void swap(unsigned char* a, unsigned char* b)
{
	unsigned char temp = *a;
	*a = *b;
	*b = temp;
}

ECode CRc4::Encrypt(char* key,  char*input, char* result)
{
	if(NULL == key || NULL == input || NULL == result)
	{
		return -1;
	}

	unsigned char S[256] = {0};
	int keylen = strlen(key);
	int i, j = 0;
	for(i=0; i<256; ++i)
	{
		S[i] = i;	
	}
	
	for(i=0; i<256; ++i)
	{
		j = (j + S[i] + key[i % keylen]) % 256;	
		swap(&S[i], &S[j]);
	}
	int m = 0;
	char k;
	i = 0; 
	j = 0;
	int inputlen = strlen(input);
	for(m=0; m<inputlen; ++m)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;	
		swap(&S[i], &S[j]);
		k = input[m] ^ S[(S[i] + S[j]) % 256];
		result[m] = k;
	}
	return 0;
}

ECode CRc4::Decrypt(char* key, char* input, char* result)
{
	return Encrypt(key, input, result);
}
