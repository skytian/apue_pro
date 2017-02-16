#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

static void  fun_1(int);
int main(){
    if((signal(SIGSTOP,fun_1)) == SIG_ERR){
        printf("receive signal err\n");
        exit(1);
    }
    printf("before sleep\n");
    sleep(2);
    //pause();
    printf("after sleep\n");
    raise(0);
}

static void fun_1(int signo){
    printf("signal handle!\n");
}
