/***************************************
 * filename:        priv_bmpwriter.c
 * description:     impl write bmp file
 * author:          kari.zhang
 * date:            2014-07-14
 *
 * ************************************/
#include <string.h>
#include <bmpwriter.h>
#include <comm.h>

PRIVATE int write_bmp(
        FILE *fp, 
        int w, 
        int h, 
        int bpp,
        const void *data
        )
{ 
    int ret = 0;
    BITMAPFILEHEADER fileheader;
    memset(&fileheader, 0, sizeof(fileheader));
    BITMAPINFOHEADER infoheader;
    memset(&infoheader, 0, sizeof(infoheader));

    int32_t nPixelBytes  = w * h * bpp;
    fileheader.bfType    = 0x4d42;      // "BM"
    fileheader.bfOffBits = sizeof(fileheader) + sizeof(infoheader);
    fileheader.bfSize    = fileheader.bfOffBits + nPixelBytes;
    ret = fwrite(&fileheader, sizeof(fileheader), 1, fp);
    if (1 != ret) {
        LogE("Failed write bmp file header");
        return -1;
    }

    infoheader.biSize      = sizeof(infoheader);
    infoheader.biWidth     = w;
    infoheader.biHeight    = (-1) * h;
    infoheader.biPlanes    = 1;
    infoheader.biBitCount  = bpp * 8;
    infoheader.biSizeImage = nPixelBytes;
    ret = fwrite(&infoheader, sizeof(infoheader), 1, fp);
    if (1 != ret) {
        LogE("Failed write bmp info header");
        return -1;
    }

    ret = fwrite(data, nPixelBytes, 1, fp);
    if (1 != ret) {
        LogE("Failed write bmp data");
        return -1;
    }

    return 0;
}

PUBLIC int write_bmpfile(
        const char *path, 
        int w, 
        int h, 
        int bpp, 
        const void *data
        )
{
    VALIDATE_NOT_NULL2(path, data);

    FILE *fp = fopen(path, "wb");
    if (NULL == fp) {
        Log(E "Failed open file %s", path);
        return -1;
    }

    int ret = 0;
    if (write_bmp(fp, w, h, bpp, data)) {
        Log(E "Failed write bmp file");
        ret = -1;
    }
    fclose(fp);

    return ret;
}
