#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>


char buf1[] = "abcdefghijklmn";
char buf2[] = "ABCDEFGHIJKLMN";

int main() {
    int fd;
    if( (fd  = open("file.hole", O_RDWR|O_CREAT)) < 0 ){
        printf("can not create file.hole\n");
        exit(0);
    }
    if(lseek(fd, 0, SEEK_END) == -1) {
        printf("can not seek file.hole\n");
        exit(0);
    }
    if(write(fd, buf1, 14) != 14) {
        printf("can not write file.hole\n");
        exit(0);
    }

    if(lseek(fd, 32, SEEK_CUR) == -1) {
        printf("can not seek file.hole\n");
        exit(0);
    }

    if(write(fd, buf2, 14) != 14) {
        printf("can not write file.hole\n");
        exit(0);
    }
    close(fd);
}

