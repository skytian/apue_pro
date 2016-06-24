/*************************************************************************
    > File Name: fcntl_con.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Wed 22 Jun 2016 03:46:16 PM CST
 ************************************************************************/
#include<sys/types.h>
#include<fcntl.h>


int main(int argc, char* argv[]){
    int accmode, val;
    if(argc != 2)
        printf("please input file\n");
    val = fcntl(atoi(argv[1]), F_GETFL, 0);
    accmode = val & O_ACCMODE;
    if(accmode == O_RDONLY) printf("read only");
    else if(accmode == O_WRONLY) printf("write only");
    else if(accmode == O_RDWR) printf("write read");
    else printf("error!");

    if(val & O_APPEND) printf(",append");
    else if(val & O_NONBLOCK) printf(", nonblocking");
    //else if(val & O_SYCN) pritf(", synchronous write");
    putchar('\n');
    exit(0);
}
