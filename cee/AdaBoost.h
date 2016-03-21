/************************************
 * file name:   AdaBoost.h
 * description: AdaBoost algorithm
 * author:      kari.zhang
 * date:        2016-01-28
 ***********************************/

#ifndef __ADABOOST_H__
#define __ADABOOST_H__

#include "cee.h"
#include "Feature.h"

#include <vector>

DECL_CORE_NAMESPACE 

class Sample {
    public:
        Sample();
        Sample(bool positive);
        bool isPositive();

    private:
        bool mIsPositive;
        std::vector<Feature *> mPositiveFeatures;
        std::vector<Feature *> mNegativeFeatures;
};

class AdaBoost {
    public:
        bool setSamplePath(const char *path);
        void startTraining();

    private:
};

END_CORE_NAMESPACE 

#endif
