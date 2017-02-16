#include <stdio.h>
#include <wt_sort.h>

int main(int argc, char *argv[]){
    int len;
    int array[1024];
    int i, j;
    for(i = 0; i < argc; i++){
        array[i-1] = atoi(argv[i]);
        printf("%d", array[i]);
    }
    sort();
}
