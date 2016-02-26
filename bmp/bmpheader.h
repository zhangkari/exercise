#ifndef __BMPHEADER__H__
#define __BMPHEADER__H__

#include <stdint.h>

/**
 * use RGBQUAD to record pixel 
 * Notice:
		the sequence is BGR
 */
typedef struct {
	int8_t rgbBlue;  	// blue 
	int8_t rgbGreen; 	// green 
	int8_t rgbRed;  	// red
	int8_t rgbReserved; // reserved, may used for alpha
} __attribute__((packed)) RGBQUAD;

typedef struct {
	int8_t b;
	int8_t g;
	int8_t r;
} __attribute__((packed)) RGB_st;

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

typedef struct { 
	BITMAPINFOHEADER bmiHeader; 
	RGBQUAD bmiColors[1]; //颜色表
} __attribute__((packed)) BITMAPINFO;

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


typedef struct 
{
	BITMAPINFOHEADER* info;
	int8_t* data;
} bmpheader_st;


int read_bmpfile(const char* filename, bmpheader_st** header);
void free_bmpheader(bmpheader_st* header);


#endif
