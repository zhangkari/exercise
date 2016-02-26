/******************************
 * file:        mke_log.h
 * description: define log api
 * author:      kari.zhang
 * date:        2014-09-03
 *
 * history:
 *
 * ****************************/
#ifndef __MKE__LOG__H__
#define __MKE__LOG__H__

#include <stdio.h>

struct log_handle_t;

int turn_log_on();
int turn_log_off();
int set_log_output(FILE *fp);
int log_v(const char *tag, const char *log);
int log_d(const char *tag, const char *log);
int log_w(const char *tag, const char *log);
int log_e(const char *tag, const char *log);

#endif
