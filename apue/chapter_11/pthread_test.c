#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pthread_t ntid;

void printfids(const char *s){
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n",
            s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg){
    printfids("new thread: ");
    return((void *)0);
}

int main(void) {
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0){
        printf("err:%d can not create thread", err);
        exit(1);
    }
    printf("ntid:%lu (0x%lx)\n", (unsigned long)ntid, (unsigned long)ntid);
    printfids("main thread: ");
    sleep(1);
    exit(0);
}
