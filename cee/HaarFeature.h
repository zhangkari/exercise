/*******************************
 * file name:   HaarFeature.h
 * description: haar feature
 * author:      kari.zhang
 * date:        2016-01-28
 ******************************/

#ifndef __HAARFEATURE_H__
#define __HAARFEATURE_H__

#include "Feature.h"

DECL_CORE_NAMESPACE

class HaarFeature : public Feature {
    public:
        HaarFeature();
        virtual ~HaarFeature();
};

END_CORE_NAMESPACE

#endif
