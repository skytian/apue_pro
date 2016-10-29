#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define BUFF_SIZE 1024
int main(int argc, char *argv[]) {
    int fd;
    int str_len;
    char buf[BUFF_SIZE] = "test cache io\n";
    char buf_f[BUFF_SIZE];
    char buf_r[BUFF_SIZE];
    if((fd = open(argv[1], O_RDWR)) > 0)
        write(fd, buf, strlen(buf));
    fputs(argv[1], buf, strlen(buf));
    fgets(argv[1], BUFF_SIZE,buf_f);
    str_len = read(fd,buf,BUFF_SIZE);

    printf("buf_f: %s , buf_r %s\n", buf_f, buf_r);
}
