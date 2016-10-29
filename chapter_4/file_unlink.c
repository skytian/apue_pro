#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf[] = "test for log.txt of unlink functioni!\n";
    if( (fd = open("log.txt", O_RDWR|O_CREAT)) <0) {
        printf("open log.txt error!\n");
        exit(1);
    }
    if(write(fd,buf,16) != 16)
        printf("write error!\n");
#if 1
    if(unlink("log.txt") > 0) {
        printf("unlink log.txt error!\n");
        exit(1);
    }
#endif
    sleep(5);
    exit(0);
}
