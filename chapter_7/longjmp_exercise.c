*************************************************************************
    > File Name: longjmp.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 26 Sep 2016 05:23:21 PM CST
 ************************************************************************/

#include<stdio.h>
#include<setjmp.h>
#include<stdlib.h>

#define MAXLINE 2048
void do_line(char *line);
jmp_buf jmpbuffer;

int main(void) {

	char line[MAXLINE];
	if(setjmp(jmpbuffer) != 0) 
		printf("setjmp error!\n");
	while (fgets(line, MAXLINE,stdin) != NULL)
		do_line(line);
	exit(0);
}

void do_line(char *line) {
	printf("do line\n");
	longjmp(jmpbuffer, 0);
	printf("%s\n", line);
	exit(0);
}
