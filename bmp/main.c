#include <stdio.h>
#include "errcode.h"
#include "bmpheader.h"

void main(int argc, char** argv)
{
	if(2 != argc)
	{
		printf("Usage:\n imgutil    filename\n");
		return;
	}

	bmpheader_st* header = NULL;
	read_bmpheader(argv[1], &header) ;

	free_bmpheader(header);
}
