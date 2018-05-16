#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>


#define MAX_LEN 		1024
#define SERVER_PORT 	6666
#define SERVER_ADDR		"127.0.0.1"
#define SOCKFD_MAX		100

void do_client_func(FILE *fp,int sock_fd)
{
	int n;
	char send_str[MAX_LEN],recv_str[MAX_LEN];
	while(fgets(send_str,MAX_LEN,fp) != NULL)
	{
		if(write(sock_fd,send_str,strlen(send_str)) < 0)
		{
			perror("write error\n");
			exit(-1);			
		}
		if((n = read(sock_fd,recv_str,MAX_LEN)) < 0)
		{
			perror("read error\n");
			exit(-1);
		}
		recv_str[n-1] = '\0';
		fputs(recv_str,stdout);
		fputs("\n",stdout);
	}
}


int main()
{
	int sock_fd;
	struct sockaddr_in server_addr;

	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sock_fd)
	{
		perror("socket error\n");
		exit(-1);
	}
	bzero(&server_addr,sizeof(server_addr));

	server_addr.sin_family 		= AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	server_addr.sin_port 		= htons(SERVER_PORT);

	if((connect(sock_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0))
	{
		perror("connect error\n");
		exit(-1);		
	}
	do_client_func(stdin,sock_fd);
	return 0;
}