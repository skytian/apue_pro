#include "common.h"

void pr_exit(int status) {
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WEXITSTATUS(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)":"");
#else
    "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

void err_sys(const char *buf) {
    printf("%s", buf);
    exit(1);
}

void pr_mask(const char *str){
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    if(sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error!");
    }
}
