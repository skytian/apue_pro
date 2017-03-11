/*************************************************************************
    > File Name: server.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 06 Mar 2017 10:48:37 AM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include"util.h"

#define MAXEV   1024
#define MAXLINE 4096
#define PORT    80



void daemonize(void){
	int fd;

	if(fork() != 0) exit(0);/*if parent exit*/

	setsid();

	if((fd = open("/dev/null", O_RDWR, 0)) != -1){
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if(fd > STDERR_FILENO) close(fd);
	}
}

static void sigShutdownHandler(int sig){
	char *msg;
	switch (sig){
		case SIGINT:
			msg = "Received SIGINT schuduling shutdown...";
			break;
		case SIGTERM:
			msg = "Received SIGTERM schuduling shutdown...";
			break;
		default:
			msg = "Receiced shutdown signal, schueduling shutdown...";
	}
	exit(0);
}

static void setupSignalHandlers(void){
	struct sigaction act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigShutdownHandler;
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	return;
}

static void processSignal(void){
	signal(SIGHUP, SIG_IGN);//ignore when session close
	signal(SIGPIPE, SIG_IGN);//ignore when pipe close
	setupSignalHandlers();

}

void (*func)(char *, char* );

void processRecv(char *data, char *request, void (*func)(char *, char *)){
   return (*func)(data, request); 
}

int main(int argc, char **argv){
	int j = 0, mode = 0;
	int backgroud = 0;


	int ev_fd, ser_fd, con_fd, nfds;
	int rev_size = 0;
	char buf[MAXLINE];
	char req[MAXLINE];
	socklen_t slen;
	struct sockaddr_in ser_addr, cli_addr;
	struct epoll_event ev;
	struct epoll_event events[MAXEV];

    void (*pfunc)(char *, char *) = NULL;

	while(j != argc){
		if(argv[j][0] == '-'){
			if(strcmp(argv[j], "-b") == 0){
				backgroud = 1;	
			}
			else if(strcmp(argv[j], "-t") == 0){
				mode = 0;
                pfunc = &tcpReply;
			}
			else if(strcmp(argv[j], "-h") == 0){
				mode = 1;
                pfunc = &httpReply;
			}
			else if(strcmp(argv[j], "-s") == 0){
				mode = 2;
			}
			else{
				printf("wrong command para:%s", argv[j]);
				exit(0);
			}
		}
		j++;
	}
	//set backgroud mode 
	if(backgroud) daemonize();

	//run tcp http or soap mode 
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
                if(rev_size > 0){
                    buf[rev_size] = '\0';
                    processRecv(buf, req, pfunc);
                    printf("receive buf:%s rev_size:%d from client!\n", buf, rev_size);
                    printf("send request:%s size:%d to client!\n", req, (int)strlen(req));
                    write(events[i].data.fd, req, strlen(req)+1);
                }
                else {
                    printf("disconnect one client!\n");
                    epoll_ctl(ev_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                }
            }
        }
    }
}
