#include"../common/common.h"

int sig_int();
int sig_int_flag;
int main(void) {
    if(signal(SIGINT, sig_int)){
        err_sys("can not catch SIGINT");
    } else
        printf("catch SIGINT\n");
    while(sig_int_flag == 0){
        pause();
    }
}

int sig_int(){
    signal(SIGINT, sig_int);
    printf("catch SIGINT\n");
    sig_int_flag = 0;
}
