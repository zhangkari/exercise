#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "IceShell.h"

int main(int argc, char** argv)
{
	ShowManual();
	char buffer[64] = {0};

	while(1)
	{
		printf(">");
		memset(buffer, 0, 64);
		fgets(buffer, 63, stdin);	
		char* result = NULL;
		int cmd = AnalyzeCmd(buffer, &result);
		if(SHELL_CMD_EXIT == cmd)
		{
			FreeAnalyzeResult(result);
			break;
		}
		else if(SHELL_CMD_INVALID == cmd)
		{
			printf("Invalid command.\n");
			FreeAnalyzeResult(result);
			continue;
		}
		ExecShell(cmd, result);
		FreeAnalyzeResult(result);
	}
}

int AnalyzeCmd(char* cmd, char** result)
{
	if(0 == strncmp(cmd, ".exit", 5))
	{
		*result = NULL;
		return SHELL_CMD_EXIT;	
	}	
	else if(0 == strncmp(cmd, ".start", 6))
	{
		*result = NULL;
		return IceCMD_START;
	}
	else if(0 == strncmp(cmd, ".stop", 5))
	{
		*result = NULL;
		return IceCMD_STOP;
	}
	else if(0 == strncmp(cmd, ".echo", 5))
	{
		int n = strlen(cmd) - 5;
		*result = (char*)malloc(n);
		// remove the '\n' by terminal input
		//		strncpy(*result, cmd+5, n-5-1);
		//		strcat(*result, 0);
		strcpy(*result, cmd+6);
		return IceCMD_ECHO;
	}
	else
	{
		return SHELL_CMD_INVALID;
	}
}


void ExecShell(int cmd, char* arg)
{
	if(cmd == IceCMD_START)
	{
		printf("staring server\n");
		int ret = Send2Server(IceCMD_START);
		if(ret < 0)
		{
			printf("start failed\n");
		}
	}
	else if(cmd == IceCMD_STOP)
	{
		printf("stopping server\n");
		int ret = Send2Server(IceCMD_STOP);
		if(ret < 0)
		{
			printf("stop failed\n");
		}
	}
	else if(cmd == IceCMD_ECHO)
	{
		printf("%s\n", arg);
	}
	else
	{
		printf("Invalid command\n");
	}

}

void FreeAnalyzeResult(char* result)
{
	if(NULL != result)
	{
		free(result);
		result = NULL;
	}
}

void ShowManual()
{
	printf("%s\n", help_str);
}

int Send2Server(char value)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		printf("Failed create socket\n");
		return -1;
	}

	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(IceSERVER_PORT);	
	if(connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Failed connect to server\n");
		close(fd);
		return -1;
	}

	char flag = 0;
	if(send(fd, &value, sizeof(value), 0) < 1)
	{
		printf("Failed send to server\n");
		flag = -1;
	}

	close(fd);
	return flag;
}
