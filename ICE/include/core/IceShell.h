#ifndef __ICESHELL__H__
#define __ICESHELL__H__

#include "IceServer.h"

const char* help_str = "this is used for communicating with ICE server\n"
"command follows:\n"
"  .exit       exit shell\n"
"  .start      start ICE server\n"
"  .stop       stop ICE server\n"
"  .restart    restart ICE server\n"
"  .echo MSG   echo the Message\n";

#ifndef SHELL_CMD_EXIT
#define SHELL_CMD_EXIT 0
#endif

#ifndef SHELL_CMD_INVALID
#define SHELL_CMD_INVALID -1
#endif

/***********************************************
 * analyze the user's input argument
 ***********************************************/
int  AnalyzeCmd(char* cmd, char** analyzeResult);

/*****************************************
 * free analyzed result
 *****************************************/
void FreeAnalyzeResult(char* analyzeResult);

/*********************************
 * execute the shell
 *********************************/
void ExecShell(int cmd, char* arg);

/****************
 * show the manual
 ****************/
void ShowManual();

int Send2Server(char value);

#endif
