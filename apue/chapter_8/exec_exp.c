#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_in[] = {"USER=unknown", "PATH=/tmp",NULL};

int main() {
    pid_t pid;

    if((pid = fork()) < 0) {
        printf("fork error!\n");
        exit(0);
    }else if(pid == 0) {
        if(execle("/usr/local/bin","ps","mysrg1", "MY ARG2", (char*)0,env_init) < 0) {
            printf("execle error!\n");
            exit(0);
        }
    }

    if(waitpid(pid, NULL, 0)< 0) {
        printf("wait error!\n");
        exit(0);
    }

    if((pid = fork())< 0){
        printf("fork error!\n");
        exit(0);
    }else if(pid == 0) {
        if(execlp("ps", "ps","only 1 arg",(char *)0) < 0) {
            printf("execlp error!\n");
            exit(0);
        }
    }

    exit(0);
}
