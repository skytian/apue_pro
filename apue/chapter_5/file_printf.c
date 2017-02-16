#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 20000000;
    printf("%0d\n", i);
    printf("% d\n", i);
    printf("%+d\n", i);
    printf("%'d\n", i);
    printf("%#0x\n", i);
    printf("%12d\n", i);
    printf("%+d\n", i);
}
