#include <CpuID.h>
#include <stdio.h>

int getCpuID(char* id, int* len)
{
	if(NULL == id || NULL == len)
	{
		printf("Illegal argument, NULL pointer\n");
		return -1;
	}
	unsigned int eax32;
	unsigned int ecx32;
	unsigned int edx32;

/*
	__asm__(
			"mov $1, %eax
			cpuid
			mov %eax, eax32
			mov $3, %eax
			cpuid
			mov %ecx, ecx32
			mov %edx, edx32"
	       );
*/

	*len = 12;
	sprintf(id, "%x%x%x", eax32, ecx32, edx32);
	return 0;
}

