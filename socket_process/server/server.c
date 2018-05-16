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
#define SOCKFD_MAX		100


void do_server_func(int sock_fd)
{
	int n;
	char buf[MAX_LEN];
	while((n = read(sock_fd,buf,MAX_LEN)) > 0)
	{
		if(write(sock_fd,buf,n) < 0)
		{
			perror("write error\n");
			exit(-1);
		}
	}
}


int main()
{
	int listen_fd; 	//监听套接字
	int conn_fd;	//连接描述符，代表与客户的TCP连接

	struct sockaddr_in server_addr,client_addr;	//server和client的协议地址结构

	socklen_t len;

	//创建套接字
	listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == listen_fd)
	{
		perror("socket error\n");
		exit(-1);		
	}

	bzero(&server_addr,sizeof(server_addr));

	//server协议地址结构赋值
	server_addr.sin_family 		= AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port 		= htons(SERVER_PORT);

	//绑定server协议地址结构给监听套接字
	if(bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
	{
		perror("bind error\n");
		exit(-1);
	}

	if(listen(listen_fd,SOCKFD_MAX) == -1)
	{
		perror("listen error\n");
		exit(-1);
	}

	while(1)
	{
		len = sizeof(client_addr);
		//获取连接套接字
		conn_fd = accept(listen_fd,(struct sockaddr*)&client_addr,&len);
		if(-1 == conn_fd)
		{
			perror("accept error\n");
			exit(-1);
		}
		do_server_func(conn_fd);
		close(conn_fd);
	}
	close(listen_fd);
	return 0;	
}
