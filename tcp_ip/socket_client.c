#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096

int main(int argc, char *argv[]){
    int sockfd, n;
    char recvline[MAXLINE], sendline[MAXLINE];
    struct sockaddr_in servaddr;

    if(argc != 2){
        printf("useage: ./client <ipaddr>i\n");
        exit(0);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error!\n");
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error!\n");
        exit(0);
    }
    printf("send msg to server:\n");
    fgets(sendline, MAXLINE, stdin);
    if(send(sockfd, sendline, strlen(sendline), 0) < 0){
        printf("send msg error!\n");
        exit(0);
    }
    recv(sockfd, recvline, MAXLINE, 0);
    printf("recv:%s", recvline);
    close(sockfd);
}
