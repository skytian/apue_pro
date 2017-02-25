#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char*argv[]){
    int socket_fd, conn_fd;
    char send_buf[MAXLINE];
    char recv_buf[MAXLINE];
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    //servaddr.sin_addr.s_addr = inet_addr("172.0.0.1");
    inet_pton(AF_INET, "localhost", &servaddr.sin_addr);

    if(connect(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error!\n");
        exit(0);
    }
    while(1){
        memset(send_buf, 0, sizeof(send_buf));
        memset(recv_buf, 0, sizeof(recv_buf));
        fgets(send_buf, MAXLINE, stdin);
        send(socket_fd, send_buf, MAXLINE, 0);
        if(strcmp(send_buf,"exit\n") == 0)
            break;
        recv(socket_fd, recv_buf, MAXLINE, 0);
        fputs(recv_buf, stdout);
    }
    close(socket_fd);
    return 0;

}

