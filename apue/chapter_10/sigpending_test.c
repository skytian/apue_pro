#include "pr_mask.h"
#include <signal.h>


static void sig_quit(int);

int main(void) {
    sigset_t newmask, oldmask, pendmask;

    if(signal(SIGINT, sig_quit) == SIG_ERR) {
        printf("can not catch SIGQUIT");
        exit(1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error!\n");
        exit(1);
    }

    sleep(5);

    if(sigpending(&pendmask) < 0) {
        printf("sigpending error!\n");
        exit(1);
    }

    if(sigismember(&pendmask, SIGINT))
        printf("SIGQUIT pending\n");


    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        printf("SIG_SETMASK error\n");
        exit(1);
    }

    printf("SIGQUIT unblocked!\n");
    sleep(5);
    exit(0);
}

static void sig_quit(int signo) {
    printf("caught SIGINT\n");
    if(signal(SIGINT, SIG_DFL) == SIG_ERR){
        printf("can not reset SIGQUIT\n");
        exit(1);
    }
}
