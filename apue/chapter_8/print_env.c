#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("home:%s\n", getenv("HOME"));
    printf("path:%s\n", getenv("PATH"));
    printf("pwd:%s\n", getenv("PWD"));
    printf("shell:%s\n", getenv("SHELL"));
}
