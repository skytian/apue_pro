#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define MAXLINE 1024

int main(int argc, char *argv[]){
    int sock_fd;
    int n;
    struct sockaddr_in serv_addr;
    char recvline[MAXLINE];

    if(argc != 2){
        printf("usage: a.out <IPAddress>\n");
        exit(0);
    }
    //build a socket
    if( (sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("socket error!\n");
        exit(0);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0){
        printf("inet_pton error!\n");
        exit(0);
    }

    if(connect(sock_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        printf("connect error!\n");
        exit(0);
    }

    while( (n = read(sock_fd, recvline, MAXLINE)) > 0){
        recvline[n] = '\0';
        if(fputs(recvline, stdout) == EOF){
            printf("fputs error!\n");
            exit(0);
        }
    }

    if(n < 0){
        printf("read error!\n");
        exit(0);
    }
    exit(0);
}
