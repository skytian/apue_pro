#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global_var = 6;
char buf[] = "a write stdout\n";
int main() {
    int var = 5;
    pid_t pid;

    printf("before fork!\n");
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1){
        printf("write error!\n");
        exit(0);
    }

    if((pid = fork()) < 0) {
        printf("fork error!\n");
    } else if (pid == 0) {
        sleep(3);
        printf("this is child process!\n");
        var++;
        global_var++;
        printf("var:%d  global_var:%d\n", var , global_var);
    } else {
        sleep(2);
        printf("this is main process!\n");
        //var++;
        //global_var++;
        //printf("var:%d  global_var:%d\n", var , global_var);
    }
    var++;
    global_var++;
    printf("pid:%ld ppid:%ld  uid:%ld  var:%d  global_var:%d\n",(long)getpid(), (long)getppid(), (long)getuid(),  var , global_var);
    exit(0);
}
