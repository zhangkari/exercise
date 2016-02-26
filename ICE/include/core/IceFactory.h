/****************************************
 * FileName:	IceFactory.h
 * Description:	Create ICE component class
 *
 *****************************************/

#ifndef __ICEFACTORY__H__
#define __ICEFACTORY__H__

#include "IUnknow.h"

ECode CreateInstance(CLSID clsid, IUnknow** ppv);

#endif
