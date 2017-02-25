#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 1024
int main(){
    int socket_fd;
    char recv_buf[MAXLINE] = {0};
    char send_buf[MAXLINE] = {0};

    socket_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in myaddr_in;
    myaddr_in.sin_family = AF_INET;
    myaddr_in.sin_port = htons(6666);
    myaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(socket_fd, (struct sockaddr*)&myaddr_in, sizeof(myaddr_in));
    listen(socket_fd, 1000);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int connfd = accept(socket_fd, (struct sockaddr*)&client_addr, &len);

    while(1){
        memset(recv_buf, 0, sizeof(recv_buf));
        int len = recv(connfd, recv_buf, sizeof(recv_buf), 0);
        if(strlen(recv_buf)==0){
            continue;
        }
        if(strcmp(recv_buf, "exit\n") == 0){
            printf("recv exit!\n");
            break;
        }
        printf("recv:%s\n", recv_buf);
        sprintf(send_buf, "%s from server!\n", recv_buf);
        send(connfd, send_buf, strlen(send_buf), 0);
        printf("send:%s\n", send_buf);
    }
    close(connfd);
    close(socket_fd);
    return 0;
}
