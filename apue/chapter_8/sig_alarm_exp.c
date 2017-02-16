#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static void sig_alrm(int signo){

}

unsigned int sleep1(unsigned int seconds){
    if(signal(SIGALRM, sig_alrm) == SIG_ERR)
        return(seconds);
    alarm(seconds);
    pause();
    return(alarm(0));
}
static jmp_buf env_alrm;
static void sig_alrm_1(int signo){
    longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int seconds) {
    if(signal(SIGALRM, sig_alrm_1) == SIG_ERR)
        return(seconds);
    if(setjmp(env_alrm) == 0){
        alarm(seconds);
        pause();
    }
    return(alarm(0));
}

int main(int argc, char *argv[]){
    int seconds;
    seconds = atoi(argv[1]);
    sleep1(seconds);
    printf("after sleep1\n");
    sleep2(seconds);
    printf("after sleep2\n");
    exit(0);
}
