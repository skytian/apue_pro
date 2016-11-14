/*************************************************************************
    > File Name: epoll_server.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 14 Nov 2016 06:47:03 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>

#define IPADDRESSS  "172.0.0.1"
#define PORT	    8787
#define MAXSIZE     1024
#define LISTENQ     5
#define FDSIZE      1000
#define EPOLLEVENTS 100

static int socket_bind(const char *ip, int port);

static void do_epoll(int listenfd);

static void handle_events(innt epolled, struct epoll_event *events, int num, int listenfd, char *buf);

static void handle_accept(int epolled, int listenfd);
