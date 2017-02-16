#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#define MAXLINE 1024
static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void) {
    int n;
    char line[MAXLINE];

    if(signal(SIGALRM, sig_alrm) == SIG_ERR){
        printf("signal error!\n");
        exit(0);
    }
    if(setjmp(env_alrm) != 0){
        printf("read timeout\n");
        exit(0);
    }

    alarm(10);
    if((n = read(STDIN_FILENO, line, MAXLINE)) < 0){
        printf("read error!\n");
        exit(0);
    }
    alarm(0);
    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alrm(int signo){
    longjmp(env_alrm, 1);
}
