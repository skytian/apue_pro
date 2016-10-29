#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int fd , fd_w;
    int n;
    char buf[BUFSIZE];

    if(argc != 4) {
        printf("please enter tree para\n");
        exit(0);
    }
    if(!(fd = open(argv[1], O_RDONLY))) {
        printf("can not open file %s\n", argv[1]);
        exit(0);
    }
    if(!(fd_w = open(argv[2], O_RDWR|O_CREAT))) {
        printf("can not open file %s\n", argv[2]);
        exit(0);
    }
    while(( n = read(fd, buf, BUFSIZE)) > 0) {
        if(write(fd_w, buf,n) != n) {
            printf("write error!\n");
            exit(0);
        }

    }
    close(fd);
    close(fd_w);

    //std io
    FILE *fp = NULL;
    FILE *fp_w = NULL;
    if((fp = fopen(argv[2], "r")) == NULL) {
        printf("can not open :%s\n", argv[2]);
        exit(0);
    }
    if((fp_w = fopen(argv[3], "w")) == NULL) {
        printf("can not open :%s\n", argv[3]);
        exit(0);
    }
    while( fgets(buf,BUFSIZE,fp) ) {
        fputs(buf, stdout);
        fputs(buf, fp_w);
    }

    fclose(fp);
    fclose(fp_w);

}
