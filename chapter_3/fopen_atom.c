/*************************************************************************
    > File Name: fopen_atom.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Tue 05 Jul 2016 06:33:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main(int argv, char *argc[]) {
	char *pathname;
	int fd;
	mode_t mode;
	if(argv == 2) {
		pathname = argc[1];
		if((fd = open(pathname, O_WRONLY)) < 0) {
			if((fd = creat(pathname, mode)) < 0)
				printf("create error!");
		}
		else {
			printf("open success!\n");
		}
	}
	else
		printf("argv is not 2!\n");
}
