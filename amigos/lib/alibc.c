#include "alibc.h"

void puts(const char* str)
{
	const char* p = str;
	while(*p)
	{
		print(*p);
		++p;	
	}	
}

void putInt(int value)
{

	char s[10]={0};
	int i = 0;
	while(value)
	{
		s[i] = value % 10;
		s[i] += '0';
		value /= 10;
		++i;
	}

	while(i>=0)
	{
		print(s[--i]);
	}

	print('\n');
}
