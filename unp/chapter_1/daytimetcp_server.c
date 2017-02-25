#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <time.h>
#include <string.h>

#define MAXLINE 1024
#define LISTENQ 100

int err_sys(char *str){
    printf("%s", str);
    exit(0);
}
int main(){
    int sock_fd, conn_fd;
    char buff[MAXLINE];
    struct sockaddr_in serv_addr;
    time_t tm;
    int n;

    if( (sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_sys("socket error!\n");
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ){
        err_sys("bind error!\n");
    }

    if( listen(sock_fd, LISTENQ)  < 0){
        err_sys("listen error!\n");
    }

    for( ; ; ){
        if( (conn_fd = accept(sock_fd, NULL, NULL)) < 0 ){
            err_sys("accept error!\n");
        }
        tm = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&tm));
        printf("%s", buff);
        n = write(conn_fd, buff, strlen(buff));
        if(n < 0){
            err_sys("write error!\n");
        }
        if( close(conn_fd) < 0 ){
            err_sys("close connfd!\n");
        }
    }

}
