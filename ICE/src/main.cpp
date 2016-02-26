#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "IID.h"
#include "CLSID.h"
#include "IAdvMath.h"
#include "ErrorCode.h"
#include "IceFactory.h"
#include "ISimpleMath.h"
#include <CurrentTime.h>
#include <MacAddr.h>
#include <GenGuid.h>
#include <IRc4.h>
#include <Stack.h>
#include <String.h>
#include <Tree.h>
#include <drawTree.h>
#include <Queue.h>

int main()
{

#if 0
	IUnknow* pUnknow = NULL;
	ECode ecRet = CreateInstance(CLSID_CMATH, &pUnknow);
	if(ecRet != NOERROR)
	{
		printf("Failed Create Instance,%s\n", GetErrorMessage(ecRet));
		return -1;
	}

	ISimpleMath* pSimpleMath = NULL;

	if(!pUnknow->QueryInterface(IID_ISimpleMath, (void**)&pSimpleMath))
	{
		if(pSimpleMath)
		{
			printf("100+24=%d\n", pSimpleMath->Add(100, 24) );
		}
	}

	IAdvMath* pAdvMath = NULL;

	if(!pUnknow->QueryInterface(IID_IAdvanceMath, (void**)&pAdvMath))
	{
		if(pAdvMath)
		{

			printf("3^4=%d\n", pAdvMath->Pow(3, 4) );
		}
	}

	char key[] = "good job!\0";
	char input[] = "this is original string\0";
	char result[64] = {0};
	char origin[64] = {0};
	printf("origin:%s\n", input);

	ecRet = CreateInstance(CLSID_CRc4, &pUnknow);
	if(NOERROR != ecRet)
	{
		printf("Failed Create CLSID_CRc4\n");
		return 0;	
	}

	IRc4* pRC4 = NULL;
	if(!pUnknow->QueryInterface(IID_IRc4Encrypt, (void**)&pRC4))
	{
		pRC4->Encrypt(key, input, result);
		printf("encrpyt:%s\n", result);
	}
	if(!pUnknow->QueryInterface(IID_IRc4Decrypt, (void**)&pRC4))
	{
		pRC4->Decrypt(key, result, origin);
		printf("decrpyt:%s\n", origin);
	}

	GUID guid;
	GenGuid(&guid);
	PrintGuid(guid);
	printf("\n");	

	Stack<int *> stack;
	int a = 10;
	stack.Push(&a);
	int* p;
	stack.Pop(p);
	printf("%d\n", *p);

	String s1("good");
	String s2(" job");
	String s3 = s1 + s2;

	printf("s3:%s\n", s3.string());


#endif





}
