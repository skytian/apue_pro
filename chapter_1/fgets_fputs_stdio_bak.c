/*************************************************************************
    > File Name: fgets_fputs_stdio.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Fri 17 Jun 2016 04:06:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


#define BUFFSIZE 4096
int main(void) {
	char buf[BUFFSIZE];
	while ( fgets(buf,BUFFSIZE,stdin) != NULL)
		if (fputs(buf,stdout) == EOF) {
			printf("output error!");
			exit(0);
		}
}
