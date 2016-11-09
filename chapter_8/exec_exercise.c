/*************************************************************************
    > File Name: exec_exercise.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Fri 30 Sep 2016 11:24:46 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL};

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		printf("fork error!\n");
		exit(1);
	} else if (pid == 0) {
		if(execle("/home/sar/bin/echoall", "echoall", "myarg1","MY ARG2", (char *)0, env_init) < 0) {
				printf("execle error!\n");
				exit(1);
		}
	}

	if(waitpid(pid, NULL, 0) < 0) {
		printf("wait error!\n");
		exit(1);
	}

	if ((pid = fork()) < 0) {
		printf("fork  error!\n");
		exit(1);
	} else if  (pid == 0) {
		if(execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0){
			printf("execlp error!\n");
			exit(1);
		}
	}

	exit(0);
}

