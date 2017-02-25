#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(int argc, char **argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("create socket error!");
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        printf("bind socket error!");
    if( listen(listenfd, 10) == -1){
        printf("listen socket error!\n");
        exit(0);
    }
    while(1){
        if((connfd = accept(listenfd, NULL, NULL)) == -1){
            printf("accept socket error!\n");
            continue;
        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\n';
        printf("recv msg from client: %s\n", buff);
        n = send(connfd, buff, strlen(buff), 0);
        close(connfd);
    }
}

