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
#define FDSIZE      1024
#define EPOLLEVENTS 100

static void do_epoll(int fd);

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
	do_epoll(fd);
	/*for( ; ; ){
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
	close(fd);*/
	return 0;
}

static  void do_epoll(int listenfd){
	int epollfd, cli_sockfd;
	int ret,num;
	int i, n;
	int fd;
	int addrlen;
	char buf[MAXSIZE];
	char recvline[MAXSIZE];
	char sendline[MAXSIZE];
	struct sockaddr_in cli_addr;
	struct epoll_event events[EPOLLEVENTS];
	epollfd = epoll_create(FDSIZE);
	events[0].events = EPOLLIN;
	events[0].data.fd = listenfd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &events[0]);
	addrlen = sizeof(struct sockaddr);
	for( ; ; ){
		num = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
		for(i = 0; i < num; i++){
			fd = events[i].data.fd;
			if( fd == listenfd && (events[i].events & EPOLLIN)){
				cli_sockfd = accept(fd ,(struct sockaddr *)&cli_addr, &addrlen);
				if(cli_sockfd == -1){
					perror("accept error: ");
				}
				struct epoll_event ev;
				ev.events = EPOLLIN;
				ev.data.fd = cli_sockfd;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, cli_sockfd, &ev);
			}
			else if(events[i].events & EPOLLIN){
				n = recv(cli_sockfd, recvline, MAXSIZE, 0);
				if(n == -1){
					perror("read error: ");
					close(fd);
					epoll_ctl(epollfd, EPOLL_CTL_DEL, cli_sockfd, &events[i]);
				}
				else if(n == 0){
					perror("client close: ");
					close(fd);
					epoll_ctl(epollfd, EPOLL_CTL_DEL, cli_sockfd, &events[i]);
				}
				else {
					printf("read message is : %s", recvline);
					events[i].events = EPOLLOUT;
					epoll_ctl(epollfd, EPOLL_CTL_MOD, cli_sockfd, &events[i]);
				}

			}
			else if(events[i].events & EPOLLOUT){
				sprintf(sendline, "%s", "send msg\n");
				printf("%s", sendline);
				n = send(cli_sockfd, sendline, strlen(sendline), 0);
				if( n == -1){
					perror("write error: ");
					close(fd);
					epoll_ctl(epollfd, EPOLL_CTL_DEL, cli_sockfd, &events[i]);
				}
				else{
					events[i].events = EPOLLIN;
					epoll_ctl(epollfd, EPOLL_CTL_MOD, cli_sockfd, &events[i]);
				}
			}
		}
	}
}