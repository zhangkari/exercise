#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "IceServer.h"

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("%s type arg\n", argv[0]);
		printf("\tskt	--socket\n");
		printf("\t  	  -d daemon\n");
		printf("\tshm	--share memory\n");
		printf("\tmap	--mmap\n");
		return -1;
	}	

	if(0 == strcmp(argv[1], "skt"))
	{
		printf("Talk by socket\n");
		socket_talk(argc, argv);
	}
	if(0 == strcmp(argv[1], "map"))
	{
		printf("Talk by mmap\n");
		mmap_talk();
	}
}

int socket_talk(int argc, char** argv)
{
	FILE* fp_log = NULL;

	if(argc == 3 && 0 == strcmp(argv[2], "-d"))
	{
		init_daemon();
	}

	int fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_server < 0)
	{
		fp_log = fopen(IceSERVER_LOG_PATH, "a+");
		fprintf(fp_log, "Failed create socket, %s\n", strerror(errno));
		fclose(fp_log);
		return -1;
	}

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //htons(INADDR_ANY);
	server_addr.sin_port = htons(IceSERVER_PORT);

	if(bind(fd_server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{

		fp_log = fopen(IceSERVER_LOG_PATH, "a+");
		fprintf(fp_log, "Failed bind server address,%s\n", strerror(errno));
		fclose(fp_log);
		close(fd_server);
		return -1;
	}

	if(listen(fd_server, 5) < 0)
	{
		fp_log = fopen(IceSERVER_LOG_PATH, "a+");
		fprintf(fp_log, "Failed listen socket,%s\n", strerror(errno));
		fclose(fp_log);
		close(fd_server);
		return -1;
	}

	char runFlag = 1;

	while(runFlag)
	{
		struct sockaddr_in client_addr;
		socklen_t addrlen = sizeof(client_addr);
		int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
		if(fd_client < 0)
		{
			//close(fd_client);
			continue;
		}

		fp_log = fopen(IceSERVER_LOG_PATH, "a+");
		fprintf(fp_log, "accpet from:%s\n", inet_ntoa(client_addr.sin_addr) );
		fclose(fp_log);

		unsigned char recvChar;
		int recvlen = recv(fd_client, &recvChar, 1, 0);
		if(recvlen < 0)
		{
			close(fd_client);
			continue;
		}

		
		fp_log = fopen(IceSERVER_LOG_PATH, "a+");
		fprintf(fp_log, "recv:%d\n", recvChar);
		fclose(fp_log);

		switch(recvChar)
		{
			case IceCMD_STOP:
				runFlag = 0;
				break;
		}

		close(fd_client);
	}

	close(fd_server);
}

int init_daemon()
{
	printf("Switching to daemon...\n");
	pid_t pid = fork();
	if(pid > 0)
	{
		exit(0); //exit the parent process
	}
	else if(pid < 0)
	{
		exit(1); // Failed fork
	}

	setsid();
	pid = fork();
	if(pid > 0)
	{
		exit(0); //exit the parent proces
	}
	else if(pid < 0)
	{
		exit(1); // Failed fork
	}

	int i;
	for(i=0; i<NOFILE; ++i)
	{
		close(i);
	}

	chdir("/");
	umask(0);
	return 0;
}


int mmap_talk()
{
	int fd = open(IceSERVER_MAP_FILE_PATH, O_RDWR|O_CREAT);	
	if(fd < 0)
	{
		printf("Failed open %s,%s\n", IceSERVER_MAP_FILE_PATH, strerror(errno));
		return -1;
	}

	char* addr_map = (char*)mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(MAP_FAILED == addr_map)
	{
		printf("Failed mmap,%s\n", strerror(errno));
		return -1;
	}	

	while(1)
	{
		printf("%s\n", addr_map);
		sleep(5);
		if(0 == strcmp(addr_map, "exit"))
		{
			break;
		}
	}

	munmap(addr_map, 1024);

	return 0;
}
