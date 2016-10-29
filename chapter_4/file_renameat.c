#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {
    system("ls -l");
    int fd_1, fd_2;
    if(fd_1 = open("foo_rename", O_WRONLY) < 0) {
        printf("open foo_rename error!\n");
        exit(1);
    }
    if(fd_2 = open("foo_renameat", O_WRONLY | O_CREAT) < 0) {
        printf("open foo_renameat error!\n");
        exit(1);
    }
    if( renameat(fd_1,"/home/tim/apue_pro/chapter_4/foo_rename",fd_2, "/home/tim/apue_pro/chapter_4/foo_renameat") < 0 ) {
        printf("rename foo error!\n");
        exit(1);
    }
    system("ls -l");
    exit(0);
}


