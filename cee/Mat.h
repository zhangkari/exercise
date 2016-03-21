/************************************
 * file name:   Mat.h
 * description: define Matrix
 * author:      kari.zhang
 * date:        2016-01-28
 ***********************************/

#ifndef __MAT_H__
#define __MAT_H__

#include "cee.h"

DECL_CORE_NAMESPACE

class Mat {
    public:
        Mat(int rows);
        Mat(int rows, int colus);
        virtual ~Mat();
        bool read(const char *file);
        bool read(byte *buff, int rows, int cols);
};

END_CORE_NAMESPACE

#endif
