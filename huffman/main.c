#include <stdio.h>
#include "huffman.h"
#include <stdlib.h>

void print_usage();
void parse_args(int argc, char** argv);

int main(int argc, char** argv)
{
	parse_args(argc, argv);
}

void print_usage()
{
	printf("Invalid arguments. \n"
			"Usage:huff [-c, -d, -h] filenameIn filenameOut\n"
			"\t -c compress\n"
			"\t -d decompress\n"
			"\t -h for help\n");
}

void parse_args(int argc, char** argv)
{
	if(argc != 4 && argc != 2)
	{
		print_usage();
		exit(1);
	}	

	if(argc == 2 && !strncmp(argv[1], "-h", 2))
	{
		print_usage();
		return;
	}

	if(!strncmp(argv[1], "-c", 2))
	{
		hfm_compress_file(argv[2], argv[3]);
		return ;
	}
	else if(!strncmp(argv[1], "-d", 2))
	{
		hfm_decompress_file(argv[2], argv[3]);
		return;
	}
	else
	{
		print_usage();
		exit(1);
	}	
}
