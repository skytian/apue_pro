/*************************************************************************
	> File Name: util.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月11日 星期六 15时21分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"tis_http.h"

void tcpReply(char *data, char *request){
    sprintf(request, "tcp reply:receive %s", data);
}

void httpReply(char *data, char *request){
    //int ret;
    //ret = judgeHttpHeader(data, request);
    char content[1024] = "\r\n<head><title>tis server</title></head>\r\n<body bgcolor=\"white\">\r\n<center><h1>start tis server</h1></center>\r\n<hr><center>tis/0.0.1</center>\r\n</body>\r\n</html>\r\n";
    printf("length:%lu", strlen(content)+1);
    sprintf(request, "HTTP/1.1 200 OK\r\nDate:Sun,12 Mar 2017 09:37:45 GMT\r\nServer:test tis\r\nContent-length:%lu\r\nContent-Type: text/html;charset=gbk\r\nCache-Control: private\r\nConnection: Keep-Alive\r\n\r\n<html>\r\n<head><title>tis server</title></head>\r\n<body bgcolor=\"white\">\r\n<center><h1>start tis server</h1></center>\r\n<hr><center>tis/0.0.1</center>\r\n</body>\r\n</html>\r\n", strlen(content)+1);
}

void soapReply(char *data, char *request){

}
