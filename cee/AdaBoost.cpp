/************************************
 * file name:   AdaBoost.h
 * description: AdaBoost algorithm
 * author:      kari.zhang
 * date:        2016-01-28
 ***********************************/

#include "AdaBoost.h"

DECL_CORE_NAMESPACE 

Sample::Sample() {
    mIsPositive = true;
}

Sample::Sample(bool positive) {
    mIsPositive = positive;
}

bool Sample::isPositive() {
    return mIsPositive;
}

bool AdaBoost::setSamplePath(const char *path) {

}

void AdaBoost::startTraining() {

}

END_CORE_NAMESPACE 
