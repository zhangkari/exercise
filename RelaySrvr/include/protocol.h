/******************************
 * file name:   protocol.h
 * description: define protocol
 * author:      Kari.Zhang
 * date:        2015-03-04
 *
 * modifications:
 *
 * ****************************/

#ifndef __PROTOCOL__H__
#define __PROTOCOL__H__

#include <comm.h>

#define DEFAULT_PORT 8099

typedef struct msgheader_t {
    enum {
		INVALID		= 0x00,		// invalid
        REQ_CONNECT = 0xa0,     // request connect
        RES_CONNECT = 0xa1,     // response connect
        REQ_RELAY	= 0xa2,     // request relay
        RES_RELAY	= 0xa3,     // response relay
    } message_type;

    enum {
        DEVICE_SLAVE  = 0xb0,   // be-controlled device 
        DEVICE_MASTER = 0xb1,   // master device
        DEVICE_ADMIN  = 0xb2,   // administractor
    } device_type;

    uint32 ip;
    uint32 port;
    uint32 token;
} msgheader_t;

/**
 * validate the message header
 * return:
 *      0  success
 *      -1 failed
 */
int validate_msgheader(msgheader_t *header);

#endif
