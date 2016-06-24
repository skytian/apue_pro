/*************************************************************************
    > File Name: copy_file.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 20 Jun 2016 01:38:06 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFF_SIZE 1024

int main(int argv, char* argc[]) {
	int src_fd,dest_fd;
	char buff[BUFF_SIZE];
	int read_len = 0;
	if(argv == 3) {
		if((src_fd = open(argc[1],O_RDONLY)) > 0) {
            int dup_fd = open(argc[1], O_RDONLY);
            int fd = dup2(dup_fd,src_fd);
            printf("src_fd: %d\n dup_fd: %d\n fd: %d\n", src_fd, dup_fd, fd);
			lseek(src_fd, 20, SEEK_SET);
			while((read_len = read(src_fd, buff, BUFF_SIZE-1)) > 0){
				if((dest_fd = open(argc[2], O_CREAT|O_WRONLY|O_TRUNC)) > 0) {
					write(dest_fd, buff, read_len);
                    printf("read_len: %d\n buff: %s\n", read_len,buff);
                }
				else {
					printf("can not create [%s]!\n", argc[2]);
                    exit(0);
                }
			}
			close(src_fd);
			close(dest_fd);
		}
		else
			printf("can not open file [%s]!\n", argc[1]);
	}
	else {
		printf("please input source file and destination file!\n");
	}
}
