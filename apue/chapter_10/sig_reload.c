#include"../common/common.h"
#include<pwd.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;
    printf("in signal handle\n");
    if ((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwname(root) error");
    printf("rootptr pw_name = %s\n", rootptr->pw_name);
    alarm(1);
}

int main(void) {
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for( ; ; ){
        if((ptr = getpwnam("tim")) == NULL)
            err_sys("getpwnam error");
        printf("pw_name = %s\n", ptr->pw_name);
        if(strcmp(ptr->pw_name, "tim") != 0)
            printf("return value corrupted! pw_name = %s\n", ptr->pw_name);
    }
}
