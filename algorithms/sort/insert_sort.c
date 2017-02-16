#include <stdio.h>
#include <stdlib.h>

int  array_len(int *a);
void insert_sort(int *a, unsigned int len);
void print_array(int *a, unsigned int len);
int main(){
    int a[256] = {25, 5, 8, 4, 9, 6, 20, 10, 1,19};
    int len = array_len(a);
    print_array(a, len);
    insert_sort(a, len);
    print_array(a, len);
}
int array_len(int *a){
    int i = 0;
    while(a[i] != 0){
        i++;
    }
    return i;
}
void insert_sort(int *a, unsigned int len){
    int i, j;
    int key;
    for(i = 1; i < len; i++){
        key = a[i];
        j = i -1;
        while(j >= 0 && a[j] > key){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void print_array(int *a, unsigned int len){
    int i;
    printf("array: ");
    for(i = 0; i < len; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}
