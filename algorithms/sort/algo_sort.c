/*************************************************************************
	> File Name: algo_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2017年03月07日 星期二 22时54分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

static int partition(int *array, int low, int high){
    int i, j;
    int key = array[low];
    i = low;
    j = high;
    while(i < j){
        while(array[j] < key){
            j++;
        }
        if(array[j] > key){
            swap(&array[j], &array[i]);
        } 
        while(array[i] > key){
            i++;
        } 
        if(array[i] > key){
            swap(&array[j], &array[i]);
        } 
    }
    return i;
}

static int quickSort(int *array, int low, int high){
    int mid;
    mid = partition(array, low, high);
    quickSort(array, mid, high);
    quickSort(array, low, mid-1);
}
int *quick_sort(int *array, int len){
    quickSort(array, 0, len-1);
}

int *merge_sort(int *array, int len){

}

int *insert_sort(int *array, int len){

}

int *bubble_sort(int *array, int len){
    
}
