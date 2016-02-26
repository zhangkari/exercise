/************************************
 * filename:        bmpwriter.h
 * description:     write bmp file
 * author:          kari.zhang
 * date:            2015-01-18
 *
 * *********************************/

#ifndef __BMPWRITER__H__
#define __BMPWRITER__H__

#include <stdio.h>
#include <stdint.h>

#include <comm.h>

/**
 * use BITMAPINFOHEADER to record pixel info
 */
typedef struct { 
	int32_t biSize; 			// sizeof(me)
	int32_t biWidth; 			// pixel count in width
	int32_t biHeight; 			// pixel count in height
	int16_t biPlanes; 			// must equal 1
	int16_t biBitCount; 		// bit count of each pixel (16, 24, 32)
	int32_t biCompression;		// compression, (equal 0 means not compressed)
	int32_t biSizeImage; 		// image size in byte
	int32_t biXPelsPerMeter;	// pixel count per meter in x-coordinate 
	int32_t biYPelsPerMeter;	// pixel count per meter in y-coordinate 
	int32_t biClrUsed; 			// color count, if equal 0, biBitCount take effect
	int32_t biClrImportant; 	// important number, if 0, all are important 
} __attribute__((packed)) BITMAPINFOHEADER;

/**
 * bitmap file header info
 * Notice:
 *		the data stored from the last row to the first row
 */
typedef struct { 
	int16_t bfType; 			// file type, must equal "BM"
	int32_t bfSize; 			// file size
	int16_t bfReserved1; 		// 0
	int16_t bfReserved2; 		// 0
	int32_t bfOffBits; 			// the pixel data offset the file header
} __attribute__((packed)) BITMAPFILEHEADER;

PUBLIC  int write_bmpfile(
        const char *path,                               // file name 
        int w,                                          // width
        int h,                                          // height
        int bpp,                                        // bytes per pixel
        const void *data                                // raw data
        );
#endif
