/*******************************
 * file name:   Feature.h
 * description: feature
 * author:      kari.zhang
 * date:        2016-01-28
 ******************************/

#ifndef __FEATURE_H__
#define __FEATURE_H__

#include "cee.h"

DECL_CORE_NAMESPACE

class Feature {
    public:
        Feature();
        virtual ~Feature();
        void setX(int x);
        int getX();
        void setY(int y);
        int getY();
        void setValue(int value);
        int getValue();

protected:
        int mX;
        int mY;
        int mValue;
};

END_CORE_NAMESPACE

#endif
