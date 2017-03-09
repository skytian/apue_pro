/*************************************************************************
	> File Name: ep.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月09日 星期四 19时14分30秒
 ************************************************************************/

#include<stdio.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#define MAXEV   1024
#define MAXLINE 1024
#define PORT    8080


int main(){
    int ev_fd, ser_fd, con_fd, nfds;
    int rev_size = 0;
    char buf[MAXLINE];
    socklen_t slen;
    struct sockaddr_in ser_addr, cli_addr;
    struct epoll_event ev;
    struct epoll_event events[MAXEV];

    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT);

    if((ser_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket error!\n");
        exit(1);
    }

    if(bind(ser_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr))< 0){
        perror("bind error!");
        exit(1);
    }

    if(listen(ser_fd, 10) < 0){
        perror("listen error!");
        exit(1);
    }

    //begin epoll event
    //create epoll event
    ev_fd = epoll_create(MAXEV);

    ev.events = EPOLLIN;
    ev.data.fd = ser_fd;

    epoll_ctl(ev_fd, EPOLL_CTL_ADD, ser_fd, &ev);


    slen = sizeof(cli_addr);
    while(1){
        nfds = epoll_wait(ev_fd, events, MAXEV, -1);
        int i;
        for(i = 0; i < nfds; i++){
            if(events[i].data.fd == ser_fd){
                if((con_fd = accept(ser_fd, (struct sockaddr *)&cli_addr, &slen)) < 0){
                    printf("con_fd:%d", con_fd);
                    perror("accept error! con_fd\n");
                }
                else {
                    ev.events = EPOLLIN;
                    ev.data.fd = con_fd;
                    epoll_ctl(ev_fd, EPOLL_CTL_ADD, con_fd, &ev);
                    printf("accept client:%s!\n", inet_ntoa(cli_addr.sin_addr));
                }
            }
            else if(events[i].events & EPOLLIN){
                rev_size = read(events[i].data.fd, buf, MAXLINE);
                buf[rev_size] = '\0';
                printf("receive buf:%s rev_size:%d from client!\n", buf, rev_size);
                write(events[i].data.fd, buf, strlen(buf)+1);
            }
        }
    }
}
