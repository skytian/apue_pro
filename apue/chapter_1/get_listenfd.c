/*************************************************************************
	> File Name: get_listenfd.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月12日 星期日 00时09分21秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>

int main(){
    char *ptr;
    printf("LISTENQ:%d", LISTENQ);
    ptr = getenv("PATH");
    if(ptr != NULL)
        printf("ptr:%s\n", ptr);
    else{
        printf("null point!\n");
    }
    exit(0);
}
