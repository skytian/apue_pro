#include <stdio.h>
#include <stdlib.h>

static void my_exit1() {
    printf("first exit handler!\n");
}
static void my_exit2() {
    printf("second exit handler!\n");
}

int main() {
    if (atexit(my_exit1) != 0) {
        printf("can not register my_exit1()!\n");
    }

    //exit(1);
    if (atexit(my_exit2) != 0) {
        printf("can not register my_exit2()!\n");
    }

    printf("main is done!\n");
    return 0;
//exit(0);
}


