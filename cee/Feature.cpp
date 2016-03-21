/*******************************
 * file name:   haar_feature.cpp
 * description: haar feature
 * author:      kari.zhang
 * date:        2016-01-28
 ******************************/

#include "Feature.h"

DECL_CORE_NAMESPACE

Feature::Feature() {

}

Feature::~Feature() {

}

void Feature::setX(int x) {
    mX = x;
}

int Feature::getX() {
    return mX;
}

void Feature::setY(int y) {
    mY = y;
}

int Feature::getY() {
    return mY;
}

void Feature::setValue(int value) {
    mValue = value;
}

int Feature::getValue() {
    return mValue;
}

END_CORE_NAMESPACE
