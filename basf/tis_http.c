/*************************************************************************
	> File Name: tis_http.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月11日 星期六 15时25分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>


#define MAXURL 1024

typedef enum _http_mode{
    GET = 1,
    POST,
    HEAD,
    PUT,
    DELETE,
    TRACE,
    CONNECT,
    OPTIONS
} http_mode;

typedef struct _http_struct{
    http_mode mode;
    char route[MAXURL];
    char version[32];
} http_struct;

int judgeHttpHeader(const char *data, char *request){
    return 0;
}

