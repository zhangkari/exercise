#include "bmpheader.h"
#include "errcode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int validate_bmpfile(const BITMAPFILEHEADER* fileheader,
		const BITMAPINFOHEADER* infoheader)
{
	if(NULL == fileheader || NULL == infoheader)
		return E_NULL_POINTER;

#ifdef DEBUG
	int16_t type = fileheader->bfType;
	printf("type:%c%c\n", type&0x00ff, (type>>8)&0x00ff);
	printf("size:%d\n", fileheader->bfSize);
	printf("reserved1:%d\n", fileheader->bfReserved1);
	printf("reserved2:%d\n", fileheader->bfReserved2);
	printf("offbits:%d\n", fileheader->bfOffBits);

	printf("\n");

	printf("info size:%d\n",infoheader->biSize);
	printf("width:%d\n", infoheader->biWidth);
	printf("height:%d\n", infoheader->biHeight);
	printf("planes:%d\n", infoheader->biPlanes);
	printf("bitCount:%d\n", infoheader->biBitCount);
	printf("bitCompression:%d\n", infoheader->biCompression);
	printf("imageSize:%d\n", infoheader->biSizeImage);
	printf("X:%d\n", infoheader->biXPelsPerMeter);
	printf("Y:%d\n", infoheader->biYPelsPerMeter);
	printf("colorUsed:%d\n", infoheader->biClrUsed);
#endif

	int8_t ch1 = fileheader->bfType & 0x00ff;
	int8_t ch2 = (fileheader->bfType) >> 8 & 0x00ff;
	if(ch1 != 'B' || ch2 != 'M')
		return -1;

	if(fileheader->bfOffBits != 54)
		return -1;

	if(infoheader->biBitCount != 24)
		return -1;

	int count = fileheader->bfSize - fileheader->bfOffBits;
	if(count != infoheader->biSizeImage)
		return -1;

	return 0;
}

int read_bmpheader(const char* filename, bmpheader_st** header)
{
	if(NULL == filename || NULL == header)
	{
		return E_NULL_POINTER;
	}

	int retCode = NOERROR;
	FILE* fp = NULL;
	do
	{
		fp = fopen(filename, "rb");
		if(NULL == fp)
		{
			printf("ERROR: file %s not exist.\n", filename);
			retCode = E_FILE_NOT_EXIST;
			break;
		}

		BITMAPFILEHEADER fileheader;
		int nRead = 0;
		nRead = fread(&fileheader, sizeof(BITMAPFILEHEADER), 1, fp);
		if(1 != nRead)
		{
			printf("ERROR: Failed fread BITMAPFILEHEADER.\n");
			retCode = E_IO;
			break;
		}

		BITMAPINFOHEADER bmpheader;
		nRead = fread(&bmpheader, sizeof(bmpheader), 1, fp);
		if(1 != nRead)
		{
			printf("ERROR: Failed fread BITMAPINFOHEADER.\n");
			retCode = E_IO;
			break;
		}

		if(validate_bmpfile(&fileheader, &bmpheader) < 0)
		{
			printf("ERROR: Invalid bmp file or not supported format.\n");
			retCode = E_INVALID_FORMAT;
			break;
		}

		(*header) = (bmpheader_st*)malloc(sizeof(bmpheader_st));
		if(NULL == *header)
		{
			printf("ERROR: Failed malloc mem for bmpheader.\n");
			retCode = E_MALLOC_MEM;		
			break;
		}

		(*header)->info = (BITMAPINFOHEADER*)malloc(sizeof(bmpheader));
		if(NULL == (*header)->info)
		{
			printf("ERROR: Failed malloc mem for bmpheader.info.\n");
			free(*header);
			retCode = E_MALLOC_MEM;
			break;	
		}
		memcpy( (*header)->info, &bmpheader, sizeof(bmpheader));

		int count = bmpheader.biSizeImage;
		(*header)->data = (int8_t*)malloc(count * sizeof(int8_t));
		if(NULL == (*header)->data)
		{
			printf("ERROR: Failed malloc mem for bmpheader.data.\n");
			free( (*header)->info);
			free(*header);
			retCode = E_MALLOC_MEM;
			break;
		}

		nRead = fread( (*header)->data, count, 1, fp);
		if(1 != nRead)
		{
			printf("ERROR: Failed read bmp file data.\n");
			free( (*header)->info);
			free( (*header)->data);
			free(*header);
			retCode = E_IO;
			break;
		}

	}while(0);

	if(NULL != fp)
	{
		fclose(fp);
	}

	return retCode;

}

void free_bmpheader(bmpheader_st* header)
{
	if(NULL != header)
	{
		if(NULL != header->data)
			free (header->data);

		if(NULL != header->info)
			free(header->info);

		free(header);
	}
}
