/*************************************************************************
    > File Name: net.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Tue 07 Mar 2017 09:55:24 AM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>

#define MAXLINE 4096

int main(){
	int len;
	int size;
	char buf[MAXLINE] = {0};
	int sockfd, confd;
	struct sockaddr_in serv;
	struct sockaddr_in cliaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8765);
	serv.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	listen(sockfd, 10);
	size = sizeof(cliaddr);
	while(1){
		confd = accept(sockfd, (struct sockaddr *) &cliaddr, &size); 
		if(confd > 0){
			printf("accept!\n");
			while((len = read(confd, buf, MAXLINE))> 0){
				buf[len] = '\0';
				printf("buf:%s\n", buf);
				write(confd, buf, strlen(buf));
			}
		}
	}

}
