#ifndef __ICESERVER__H__
#define __ICESERVER__H__

#ifndef IceSERVER_LOG_PATH
#define IceSERVER_LOG_PATH  "./iceserver.log"
#endif

#ifndef IceSERVER_PORT
#define IceSERVER_PORT 1988
#endif


/**********************
 * define start command
 **********************/
#ifndef IceCMD_START
#define IceCMD_START 0x80
#endif

/**********************
 * define stop command
 **********************/
#ifndef IceCMD_STOP
#define IceCMD_STOP 0x81
#endif

/**********************
 * define echo command
 **********************/
#ifndef IceCMD_ECHO
#define IceCMD_ECHO 0x82
#endif

/**************************************
* define path for mmap file
***************************************/
#ifndef IceSERVER_MAP_FILE_PATH
#define IceSERVER_MAP_FILE_PATH "~/.ice_map_file"
#endif

/*************************************
* talk with socket method
**************************************/
int socket_talk(int argc, char** argv);

/****************
* talk with mmap
*****************/
int mmap_talk();

/************************
* init the daemon process
************************/
int init_daemon();

#endif
