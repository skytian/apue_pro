#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"algo_sort.h"

#define MAXARRAY 1024

int (*p_fn)(int *, int);

int sort(int *array, int len, int (*p_fn)(int *, int)){
	return (*p_fn)(array, len);
}


int main(int argc, char *argv[]){
	int i;
    if(argc != 2){
        printf("useage: ./sort mode\n");
        exit(0);
    }
	int array[MAXARRAY] = {9, 6, 3, 1, 4, 8, 7, 100, 88, 55, 111};
	printf("before sort:");
	for(i = 0; i < 12; i++){
		printf("%d ",array[i]);
	}
	printf("\n");
    int (*sort_fn)(int *, int) = NULL;
    if(strcmp(argv[1] ,"q") == 0)
        sort_fn= &quick_sort;
    else if(strcmp(argv[1],"b") == 0)
        sort_fn =  &bubble_sort;
    else if(strcmp(argv[1],"i") == 0)
        sort_fn =  &insert_sort;
    else if(strcmp(argv[1],"m") == 0)
        sort_fn =  &merge_sort;
    else{
        sort_fn = &quick_sort;
        printf("default quick sort!\n");
    }
	sort(array, 12, sort_fn);
	printf("after  sort:");
	for(i = 0; i < 12; i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}
