#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../common/common.h"

int main() {
    pid_t pid;

    if((pid = fork()) < 0)
        err_sys("fork error!");
    else if(pid != 0) {
        printf("main process! sleep(2)!");
        sleep(2);
        exit(2);
    }

    if((pid = fork()) < 0)
        err_sys("fork error!");
    else if(pid != 0) {
        printf("main process! sleep(4)!");
        sleep(4);
        abort();
    }

    if((pid = fork()) < 0)
        err_sys("fork error!");
    else if(pid != 0) {
        printf("main process! sleep(8)!");
        sleep(8);
        exit(0);
    }

    printf("sleep(6)!");
    sleep(6);
    kill(getpid(), SIGKILL);
    exit(6);
}
