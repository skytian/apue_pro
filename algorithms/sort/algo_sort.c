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

void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

int partition(int *array, int low, int high){
    int i, j;
    int key = array[low];
    i = low;
    j = high;
    while(i < j){
        while(array[j] > key && i < j){
            j--;
        }
        if(array[j] < key && i < j){
            swap(&array[j], &array[i]);
        }
        while(array[i] < key && i < j){
            i++;
        }
        if(array[i] > key && i < j){
            swap(&array[j], &array[i]);
            j--;
        }
    }
    //printf("i:%d", i);
    return i;
}

int quickSort(int *array, int low, int high){
    if(low < high){
        int mid;
        if(array == NULL){
            printf("null point!\n");
            exit(0);
        }
        mid = partition(array, low, high);
        quickSort(array, mid+1, high);
        quickSort(array, low, mid);
    }
    return 0;
}

int quick_sort(int *array, int len){
    int i = 0;
    if(array == NULL){
        printf("null point!\n");
        exit(0);
    }
    quickSort(array, 0, len-1);
    return 0;
}

int merge(int *array, int low, int high){
    int i, j, k;
    int mid = (high + low)/2;
    i = low;
    j = mid +1;
    k = 0;
    int *temp = (int *)malloc(sizeof(int)*(high - low +1));
    while(i <= mid && j <= high){
        if(array[i] < array[j]){
            temp[k++] = array[i++];
        }
        else if(array[i] > array[j]){
            temp[k++] = array[j++];
        }
    }
    while(j <= high){
        temp[k++] =  array[j++];
    }
    while(i <= mid){
        temp[k++] =  array[i++];
    }
    for(i = 0; i < (high -low +1); i++){
        array[low+i] = temp[i];
    }
    return 0;
}

int mergeSort(int *array, int low,  int high){
    int mid;
    if(low < high){
        mid = (high + low)/2;
        mergeSort(array, low, mid);
        mergeSort(array, mid+1, high);
        merge(array, low, high);
    }
    return 0;
}

int merge_sort(int *array, int len){
    return mergeSort(array, 0, len-1);
}

int insert_sort(int *array, int len){
    int i , j, tmp;
    j = 0;
    for(i = 1; i < len; i++){
        j = i-1;
        while(array[j] > array[j+1] && j >= 0){
            swap(&array[j], &array[j+1]);
            j--;
        }
    }

    return 0;
}

int bubble_sort(int *array, int len){
    int i, j;
    for(i = 0; i < len; i++){
        for(j = 1; j < len; j++){
            if(array[j] < array[j-1]){
                swap(&array[j-1], &array[j]);
            }
        }
    }
    return 0;
}
