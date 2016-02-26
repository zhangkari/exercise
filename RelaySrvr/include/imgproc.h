#ifndef __IMGPROC__H__
#define __IMGPROC__H__

#include <stdio.h>
#include <stdint.h>

/**
 * use rgb32_t to record 32 bits pixel 
 * Notice:
		the sequence is BGRA for windows bmp file
        i.e: We use Big Endian to store the data
 */
struct bgra32_t {
	uint8_t alpha;      // alpha
	uint8_t red;     	// red
	uint8_t green;   	// green 
	uint8_t blue;    	// blue 
} ;
typedef struct bgra32_t bgra32_s;

struct abgr32_t {
	uint8_t red;     	// red
	uint8_t green;   	// green 
	uint8_t blue;    	// blue 
    uint8_t alpha;      // alpha
} ;
typedef struct abgr32_t abgr32_s;

struct argb32_t {
    uint8_t blue;    	// blue 
    uint8_t green;   	// green 
	uint8_t red;     	// red
    uint8_t alpha;      // alpha
} ;
typedef struct argb32_t argb32_s;

struct rgba32_t {
    uint8_t alpha;      // alpha
    uint8_t blue;    	// blue 
    uint8_t green;   	// green 
	uint8_t red;     	// red
} ;
typedef struct rgba32_t rgba32_s;

/**
 * use rgb24_t to record 24 bits pixel 
 * Notice:
		the sequence is BGR for windows bmp file
 */
struct bgr24_t {
	uint8_t red;     	// red
	uint8_t green;   	// green 
	uint8_t blue;    	// blue 
} ;
typedef struct bgr24_t bgr24_s;

struct rgb24_t {
    uint8_t blue;    	// blue 
    uint8_t green;   	// green 
	uint8_t red;     	// red
} ;
typedef struct rgb24_t rgb24_s;

/**
 * use rgb16_t to record 16 bits pixel 
 * Notice:
		the sequence is BGR(5:6:5) for windows bmp file
 */
struct rgb16_t {
    uint16_t blue:5;    	// blue 
    uint16_t green:6;   	// green 
	uint16_t red:5;     	// red
} ;
typedef struct rgb16_t rgb16_s;

PUBLIC int rgba32_to_rgb24(
    rgba32_s *rgba, 
    int nPixels, 
    rgb24_s *rgb);
                    
PUBLIC int rgba32_to_bgr24(
    rgba32_s *rgba, 
    int nPixels, 
    bgr24_s *bgr);
                    
PUBLIC int argb32_to_rgb24(
    argb32_s *argb, 
    int nPixels, 
    rgb24_s *rgb);  
    
PUBLIC int argb32_to_bgr24(
    argb32_s *argb, 
    int nPixels, 
    bgr24_s *bgr); 

PUBLIC int bgra32_to_rgb24(
    bgra32_s *bgra, 
    int nPixels, 
    rgb24_s *rgb);  

PUBLIC int bgra32_to_bgr24(
    bgra32_s *bgra, 
    int nPixels, 
    bgr24_s *bgr);     

PUBLIC int abgr32_to_rgb24(
    abgr32_s *abgr, 
    int nPixels, 
    rgb24_s *rgb);
    
PUBLIC int abgr32_to_bgr24(
    abgr32_s *abgr, 
    int nPixels, 
    bgr24_s *bgr);
    
#endif
