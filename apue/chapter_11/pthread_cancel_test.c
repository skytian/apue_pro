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

void cleanup(void *arg) {
    printf("cleanup: %s\n", (char *)arg);
}
char *p_char = "pthread 1 exit!";
void *thr_fn1(void *arg){
    pthread_cleanup_push(cleanup, "thread 1 first handle")
    pthread_cleanup_push(cleanup, "thread 1 second handle")
    //char *p_char = "pthread 1 exit!\n";
    printfids("new thread 1: ");
    sleep(10);
    if(arg)
        return((void *)p_char);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void *)p_char);
}
void *thr_fn2(void *arg){
    //pthread_cleanup_push(cleanup, "thread 2 first handle")
    //pthread_cleanup_push(cleanup, "thread 2 second handle")
    printfids("new thread 2: ");
    pthread_t tid1 = (pthread_t *)arg;
    printf("thread 2 get arg tid1:%lu\n", (unsigned long)tid1);
    //if(arg)
     //   return((void *)2);
    //int ret = pthread_cancel(tid1);
    int ret = 0;
    if(ret != 0)
        printf("cancel thread 1 error!\n");
    printf("after cancel tid1\n");
    //pthread_cleanup_pop(0);
    //pthread_cleanup_pop(0);
    pthread_exit((void *)2);
}

int main(void) {
    int err;
    pthread_t tid1,tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if(err != 0){
        printf("err:%d can not create thread1", err);
        exit(1);
    }

    err = pthread_create(&tid2, NULL, thr_fn2, (void*)tid1);
    if(err != 0){
        printf("err:%d can not create thread2", err);
        exit(1);
    }
    printf("tid1:%lu (0x%lx)\n", (unsigned long)tid1, (unsigned long)tid1);
    printf("tid2:%lu (0x%lx)\n", (unsigned long)tid2, (unsigned long)tid2);
    printfids("main thread: ");
    err = pthread_join(tid1, &tret);
    if(err != 0){
        printf("err:%d can not join with  thread1", err);
        exit(1);
    }
    printf("thread 1 exit code %s\n", (char*)tret);
    err = pthread_join(tid2, &tret);
    if(err != 0){
        printf("err:%d can not join with thread2", err);
        exit(1);
    }
    printf("thread 2 exit code %ld\n", (long)tret);

 //   sleep(1);
    exit(0);
}
