#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {
    system("ls");
    if( rename("/home/tim/apue_pro/chapter_4/foo", "/home/tim/apue_pro/chapter_4/foo_rename") < 0 ) {
        printf("rename foo error!\n");
        exit(1);
    }
    system("ls");
}


