#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "eval_string.h"

static void usage();
static int parse_args(int argc, char** argv);
static int get_input(buffer_st** buff);
static int read_file(const char* fname, buffer_st** buff);

int main(int argc, char** argv)
{
	return parse_args(argc, argv);
}

void static usage()
{
	printf("Usage:\n");
	printf("calc [filename]\n");
}

int static parse_args(int argc, char** argv)
{
	int ret = 0;
	buffer_st* buffer = NULL;
	if(1 == argc)
	{
		ret = get_input(&buffer);
		if(ret >= 0)
		{
			ret = evaluate_string(buffer);
		}
	}
	else if(2 == argc)
	{
		ret = read_file(argv[1], &buffer);
		if(ret >= 0)
		{
			ret = evaluate_string(buffer);
		}
	}
	else
	{
		usage();
		ret = -1;
	}

	if(NULL != buffer)
	{
		if(NULL != buffer->data)
		{
			free(buffer->data);
			buffer->data = NULL;
		}
		free(buffer);
		buffer = NULL;
	}

	return ret;
}

static int get_input(buffer_st** buffer)
{
	*buffer = (buffer_st*)malloc(sizeof(buffer_st));
	if(NULL == *buffer)
		return -1;

	(*buffer)->data = (char*)malloc(MAX_INPUT * sizeof(char));
	if(NULL == (*buffer)->data)
	{
		return -2;
	}

	(*buffer)->data = fgets((*buffer)->data, MAX_INPUT, stdin);
	(*buffer)->length = strlen((*buffer)->data);

	return 0;
}

static int read_file(const char* fname, buffer_st** buffer)
{
	FILE* fp = fopen(fname, "r");
	if(NULL == fp)
	{
		printf("ERROR: Failed open file %s, %s\n", fname, strerror(errno));
		return -1;
	}

	int ret = 0;
	long filelen = 0;

	do
	{
		fseek(fp, 0L, SEEK_END);
		filelen = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		if(filelen > MAX_INPUT)
		{
			printf("ERROR: the file is longer than %d\n", MAX_INPUT);
			ret = -1;
			break;
		}

		*buffer = (buffer_st*)malloc(sizeof(buffer_st));
		if(NULL == *buffer)
		{
			ret = -2;
			break;	
		}

		(*buffer)->data = (char*)malloc(MAX_INPUT * sizeof(char));
		if(NULL == (*buffer)->data)
		{
			ret = -3;
			break;
		}

		if(filelen != fread((*buffer)->data, 1, filelen, fp))
		{
			printf("ERROR: failed read file %s\n", fname);
			ret = -4;
		}
		(*buffer)->length = filelen;

	}while(0);

	fclose(fp);
	return ret;
}
