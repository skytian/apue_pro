#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int print_sizeof(char *s){
    printf("function sizeof:%d %d\n", sizeof(s), sizeof(*s));
}
int main(int argc, char*argv[]){
    char s[20] = "skskfksjakfdksjd";
    printf("sizeof:%d %d\n", sizeof(s), sizeof(*s));
    print_sizeof(s);
}

