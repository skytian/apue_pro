#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct foo {
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
};
static struct foo *g_fp = NULL;
struct foo *foo_alloc(int id) {
    struct foo *fp;

    if((fp = malloc(sizeof(struct foo))) != NULL){
        fp->f_count = 1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->f_lock, NULL) != 0) {
            free(fp);
            return(NULL);
        }
    }
    return(fp);
}

void foo_hold(struct foo *fp) {
    int i;
    pthread_mutex_lock(&fp->f_lock);
    for(i = 0; i < 100; i++){
        fp->f_count++;
        printf("fp fcount:%d\n", fp->f_count);
    }
    pthread_mutex_unlock(&fp->f_lock);
}
void foo_hold_1(struct foo *fp) {
    int i;
    pthread_mutex_lock(&fp->f_lock);
    for(i = 0; i < 5; i++){
        fp->f_count++;
        printf("thread 1 fp fcount:%d\n", fp->f_count);
    }
    pthread_mutex_unlock(&fp->f_lock);
}
void foo_hold_2(struct foo *fp) {
    int i;
    pthread_mutex_lock(&fp->f_lock);
    for(i = 0; i < 5; i++){
        fp->f_count++;
        printf("thread 2 fp fcount:%d\n", fp->f_count);
    }
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp) {
    pthread_mutex_lock(&fp->f_lock);
    if(--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else {
        pthread_mutex_unlock(&fp->f_lock);
    }
}

void *thr_func1(void *argv) {
    int i;
    printf("start thread 1!\n");
    for(i = 0; i < 100; i++){
        foo_hold_1(g_fp);
    }
    printf("end of thread 1!\n");
}
void *thr_func2(void *argv) {
    int i;
    printf("start thread 2!\n");
    for(i = 0; i < 100; i++){
        foo_hold_2(g_fp);
    }
    printf("end of thread 2!\n");
}

int main(void) {
    pthread_t tid1,tid2;
    g_fp = foo_alloc(1);
    pthread_create(&tid1,NULL,thr_func1, NULL);
    pthread_create(&tid2, NULL, thr_func2, NULL);
    pause();
    foo_rele(g_fp);
    pause();
    return 0;
}
