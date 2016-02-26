/*************************************
 * filename:	nictrl.h
 * describe:	net interface control
 *
 *************************************/

#ifndef __NICTRL__H__
#define __NICTRL__H__

#include "type.h"

#ifndef LAYER_NETWORK
#define LAYER_NETWORK 0x80
#endif

#ifndef LAYER_DATA_LINK
#define LAYER_DATA_LINK 0x81
#endif


bool SetPromisc(const char* ifname, bool bSetFlag);
bool GetRawSocket(int layer, int* socketfd);

#endif
