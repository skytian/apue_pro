/*************************************************************************
    > File Name: test1.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 07 Nov 2016 03:55:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int print_char(char *p_char){
	printf("p_char:%s\n", p_char);
	return 0;
}
int main(void) {
	int i;
	char buf[128];
	sprintf(buf,"buf_test!!!");
	print_char(buf);
	exit(0);
}

