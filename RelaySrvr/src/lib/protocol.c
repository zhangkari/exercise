/******************************
 * file name:   protocol.c
 * description: define protocol
 * author:      Kari.Zhang
 * date:        2015-03-04
 *
 * modifications:
 *
 * ****************************/

#include <string.h>
#include <protocol.h>

/*
   typedef struct msgheader_t {
   enum {
   DEVICE_SLAVE,   
   DEVICE_MASTER,
   DEVICE_ADMIN
   } device_type;
   enum {
   MSG_CONNECT,
   MSG_RELAY,
   } message_type;
   uint32 token_code;
   } msgheader_t;
   */

/**
 * validate the message header
 * return:
 *      0  success
 *      -1 failed
 */
int validate_msgheader(msgheader_t *header)
{
#if 0
    if (NULL == header) {
        return -1;
    }

    char token[4];

    switch (header->device_type) {
        case DEVICE_SLAVE:
            if (0 != header->token_code) {
                return -1;
            }
            break;

        case DEVICE_MASTER:
            if (header->token_code <= 0) {
                return -1;
            }
            break;

        case DEVICE_ADMIN:
            memcpy(token, &header->token_code, 4);
            if (0 != strncmp(token, "KARI", 4)) {
                return -1;
            }
            break;

        default:
            return -1;
    }

    if (header->message_type != MSG_CONNECT
            && header->message_type != MSG_RELAY) {
        return -1;
    }

#endif

    return 0;
}
