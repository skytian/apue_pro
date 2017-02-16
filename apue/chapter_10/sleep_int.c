#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <signal.h>
#include "sleep2.h"

unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void) {
    unsigned int unslept;
    if(signal(SIGINT, sig_int) == SIG_ERR){
        printf("signal(SIGINT) error");
        exit(1);
    }
    unslept = sleep(5);
    printf("sleep2 returned: %u\n", unslept);
    exit(0);
}

static void sig_int(int signo){
    int i,j;
    volatile int k;

    printf("\nsig_int starting\n");
    for(i = 0; i < 300000; i++)
        for(j = 0; j <4000; j++)
            k += i*j;
    printf("sig_int finished\n");
}


