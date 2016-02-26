#include "comm.h"
#include "imgproc.h"

PUBLIC int rgba32_to_rgb24(
        rgba32_s *rgba, 
        int nPixels, 
        rgb24_s *rgb)
{
    VALIDATE_NOT_NULL2(rgba, rgb);
    int i = 0;
    rgba32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = rgba[i];
        (rgb + i)->red   = temp.red;
        (rgb + i)->green = temp.green;
        (rgb + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}

PUBLIC int rgba32_to_bgr24(
        rgba32_s *rgba, 
        int nPixels, 
        bgr24_s *bgr)
{
    VALIDATE_NOT_NULL2(rgba, bgr);
    int i = 0;
    rgba32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = rgba[i];
        (bgr + i)->red   = temp.red;
        (bgr + i)->green = temp.green;
        (bgr + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}

PUBLIC int argb32_to_rgb24(
        argb32_s *argb, 
        int nPixels, 
        rgb24_s *rgb)
{
    VALIDATE_NOT_NULL2(argb, rgb);
    int i = 0;
    argb32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = argb[i];
        (rgb + i)->red   = temp.red;
        (rgb + i)->green = temp.green;
        (rgb + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}    

PUBLIC int argb32_to_bgr24(
        argb32_s *argb, 
        int nPixels, 
        bgr24_s *bgr)
{
    VALIDATE_NOT_NULL2(argb, bgr);
    int i = 0;
    argb32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = argb[i];
        (bgr + i)->red   = temp.red;
        (bgr + i)->green = temp.green;
        (bgr + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}    

PUBLIC int bgra32_to_rgb24(
        bgra32_s *bgra, 
        int nPixels, 
        rgb24_s *rgb)
{
    VALIDATE_NOT_NULL2(bgra, rgb);
    int i = 0;
    bgra32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = bgra[i];
        (rgb + i)->red   = temp.red;
        (rgb + i)->green = temp.green;
        (rgb + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}    

PUBLIC int bgra32_to_bgr24(
        bgra32_s *bgra, 
        int nPixels, 
        bgr24_s *bgr)
{
    VALIDATE_NOT_NULL2(bgra, bgr);
    int i = 0;
    bgra32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = bgra[i];
        (bgr + i)->red   = temp.red;
        (bgr + i)->green = temp.green;
        (bgr + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}    

PUBLIC int abgr32_to_rgb24(
        abgr32_s *abgr, 
        int nPixels, 
        rgb24_s *rgb)
{
    VALIDATE_NOT_NULL2(abgr, rgb);
    int i = 0;
    abgr32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = abgr[i];
        (rgb + i)->red   = temp.red;
        (rgb + i)->green = temp.green;
        (rgb + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}

PUBLIC int abgr32_to_bgr24(
        abgr32_s *abgr, 
        int nPixels, 
        bgr24_s *bgr)
{
    VALIDATE_NOT_NULL2(abgr, bgr);
    int i = 0;
    abgr32_s temp;
    for (i=0; i<nPixels; ++i) {
        temp = abgr[i];
        (bgr + i)->red   = temp.red;
        (bgr + i)->green = temp.green;
        (bgr + i)->blue  = temp.blue;
    }

    if (i >= nPixels) {
        return 0;
    }

    return -1;
}
