/*************************************************************************
	> File Name: util.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月11日 星期六 15时21分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"tis_http.h"

void tcpReply(char *data, char *request){
    sprintf(request, "tcp reply:receive %s", data);
}

void httpReply(char *data, char *request){
    //int ret;
    //ret = judgeHttpHeader(data, request);
    sprintf(request, "HTTP/1.1 200 OK\r\nDate:Sat, 11 Mar 2017 09:37:45 GMT\r\n Server:test tis\r\nContent-length:0\r\nContent-Type: text/javascript;charset=gbk\r\nCache-Control: private\r\nConnection: Keep-Alive\r\n\r\n");
}

void soapReply(char *data, char *request){

}
