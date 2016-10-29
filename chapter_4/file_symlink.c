#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf[] = "test for log.txt of link function!\n";
    if( (fd = open("log.txt", O_RDWR|O_CREAT)) <0) {
        printf("open log.txt error!\n");
        exit(1);
    }
    int len = strlen(buf);
    if(write(fd,buf,len) != len)
        printf("write error!\n");
#if 1
    if(symlink("log.txt","symlink.log.txt") > 0) {
        printf("unlink log.txt error!\n");
        exit(1);
    }
#endif
    sleep(5);
    exit(0);
}
