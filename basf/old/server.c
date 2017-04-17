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

int main(int argc, char **argv){
	int j = 0, mode = 0;
	int backgroud = 0;
	while(j != argc){
		if(argv[j][0] == '-'){
			if(strcmp(argv[j], "-b") == 0){
				backgroud = 1;	
			}
			else if(strcmp(argv[j], "-t") == 0){
				mode = 0;
			}
			else if(strcmp(argv[j], "-h") == 0){
				mode = 1;
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
	while(1);
}
