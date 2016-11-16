#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>

#define IPADDR 		"localhost"
#define PORT   		8000
#define MAXSIZE 	1024

int main(){
	int fd, cli_sockfd;
	int addlen;
	int n;
	char recvline[MAXSIZE],sendline[MAXSIZE];
	struct sockaddr_in serv_in;
	struct sockaddr_in cli_addr;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		perror("socket error: ");
		exit(1);
	}
	bzero(&serv_in, sizeof(serv_in));
	serv_in.sin_family = AF_INET;
	inet_pton(AF_INET, IPADDR, &serv_in.sin_addr);
	serv_in.sin_port = htons(PORT);
	if(bind(fd, (struct sockaddr *)&serv_in, sizeof(serv_in)) == -1) {
		perror("bind error: ");
		exit(1);
	}
	if(listen(fd, 5) == -1){
		perror("listen error: ");
		exit(1);
	}
	printf("listen the port: ");

	for( ; ; ){
		addlen = sizeof(struct sockaddr);
		cli_sockfd = accept(fd ,(struct sockaddr *)&cli_addr, &addlen);
		if(cli_sockfd == -1)
		{
			perror("accept error: ");
			//exit(1);
		}
		while(1){
			printf("waiting for client...\n");
			n = recv(cli_sockfd, recvline, 1024, 0);
			if(n == -1){
				printf("recv error\n");
			}
			recvline[n] = '\n';
			printf("recv data is:%s\n", recvline);
			sprintf(sendline, "%s", "send msg");
			printf("%s", sendline);
			send(cli_sockfd, sendline, strlen(sendline), 0);
		}
		close(cli_sockfd);
	}
	close(fd);
	return 0;
}