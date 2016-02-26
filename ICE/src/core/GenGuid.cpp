#include <GenGuid.h>
#include <MacAddr.h>
#include <ErrorCode.h>
#include <CurrentTime.h>
#include <stdio.h>
#include <string.h>

ECode GenGuid(GUID* guid)
{
	if(NULL == guid)
	{
		return E_NULL_POINTER;
	}


	getCurAccurateTime((ulong*)&(guid->seconds), (ulong*)&(guid->usecond));	
	getMacAddr((char*)&(guid->macaddr), NULL);

	(guid->reserve)[0] = 0;
	(guid->reserve)[1] = 0;

	return NOERROR;
}

ECode PrintGuid(GUID guid)
{
	unsigned char buffer[24];
	memcpy(buffer, &guid, 24);

	int i;
	for(i=0; i<24; ++i)
	{
		printf("%.2x", buffer[i]);
		if((i+1)%4 == 0)
		{
			printf("-");
		}
	}
}

