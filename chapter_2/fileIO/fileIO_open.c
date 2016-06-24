/*************************************************************************
    > File Name: fileIO_open.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 20 Jun 2016 10:24:57 AM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

int main(int argv, char* argc[]) {
	int  fd, i;
	if(argv >= 2) {
		if((fd = open(argc[1], O_CREAT|O_WRONLY|O_APPEND )) > 0){

			printf("create file [%s] success!\n", argc[1]);
			if(argv >= 3) {
				for(i = 2; i< argv; i++) {
					write(fd,' ',1);
					write(fd,argc[i],strlen(argc[i]));
				}
					write(fd,'\n',1);
			}
			close(fd);
		}
		else {
			printf("create file [%s] failed!\n", argc[1]);
		}

	}
	else {
		printf("please enter the fileName!\n");	
	}

}
