/*************************************************************************
	> File Name: epoll_s.c
	> Author: 
	> Mail: 
	> Created Time: 2017年02月17日 星期五 04时54分08秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

#define MAX_EP_FD 1024

int main(int argc, char *argv[]){
    int listen_fd, ep_fd, nfds, connfd, sockfd;
    int i, n;
    char line[1024];
    socklen_t clilen;
    if(argc != 2){
        printf("useage ./epoll_s port!\n");
        exit(0);
    }
    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    //signal(SIG)
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_s;
    struct sockaddr_in client_addr;
    bzero(&sock_s, sizeof(sock_s));
    sock_s.sin_family = AF_INET;
    inet_aton("localhost", &(sock_s.sin_addr));
    sock_s.sin_port = htons(atoi(argv[1]));
    bind(listen_fd, (struct sockaddr *)&sock_s, sizeof(sock_s));
    listen(listen_fd, 5);

    struct epoll_event ev, events[20];

    ep_fd = epoll_create(MAX_EP_FD);

    ev.data.fd = listen_fd;
    ev.events = EPOLLIN|EPOLLET;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ev);
    for( ; ; ){
        nfds = epoll_wait(ep_fd, events, 20, 500);
        for(i = 0; i < nfds; ++i){
            if(events[i].data.fd == listen_fd){
		        connfd = accept(listen_fd, (struct sockaddr *)&client_addr, &clilen);
		        if(connfd < 0){
		            printf("connfd < 0");
		            exit(1);
		        }
		        char *str = inet_ntoa(client_addr.sin_addr);
		        printf("accept a connection from :%s\n",str);

		        ev.data.fd = connfd;
		        ev.events = EPOLLIN | EPOLLET;
		        epoll_ctl(ep_fd, EPOLL_CTL_ADD, connfd, &ev);
            }
            else if(events[i].events&EPOLLIN){
                printf("EPOLLIN\n"); 
                if((sockfd = events[i].data.fd) < 0)
                    continue;
                n = read(sockfd, line, 1024); 
                if(n <= 0)
                    continue;
                line[n] = '\0';
                printf("recv line:%s\n", line);
                ev.data.fd = sockfd;
                ev.events = EPOLLOUT|EPOLLET;
                epoll_ctl(ep_fd, EPOLL_CTL_MOD, sockfd, &ev);
                sprintf(line, "send data in\n");
                write(sockfd, line, strlen(line));
            }
            else if(events[i].events&EPOLLOUT){
                printf("EPOLLOUT\n"); 
                sockfd = events[i].data.fd;
                memset(line, 0, sizeof(line));
                sprintf(line, "send data out\n");
                write(sockfd, line, strlen(line)+1);
                ev.data.fd = sockfd;
                ev.events = EPOLLIN|EPOLLET;
                epoll_ctl(ep_fd, EPOLL_CTL_MOD, sockfd, &ev);
            }

        }
    }
    return 0;
}
