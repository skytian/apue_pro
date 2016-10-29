#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    char buf[1024];
    readlink(argv[1], buf, 32);
    printf("buf:%s\n",buf);
}
