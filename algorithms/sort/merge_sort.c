#include <stdio.h>
#include <unistd.h>



int merge_sort(int array[], int start, int end);
int merge(int array[], int start,int mid, int end);

int main(){
    int i;
    int array[] = { 9, 1, 8, 6, 7, 10, 2, 3};
    int len = 8;
    for( i = 0; i < 8; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    merge_sort(array, 0, 7);
    for( i = 0; i < 8; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int merge_sort(int array[], int start, int end){
    if(start < end){
        printf("start:%d end:%d\n", start, end);
        int mid = (end + start)/2;
        merge_sort(array, start, mid);
        merge_sort(array, mid+1, end);
        printf("start:%d mid:%d end:%d\n", start, mid, end);
        merge(array, start, mid, end);
    }
}

int merge(int array[], int start,int mid, int end){
    int i, j, k;
    int temp[1024];
    i = start, j = mid+1, k = 0;
    while(i <= mid && j <= end ){
        if(array[i] < array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    while (i <= mid){
        temp[k++] = array[i++];
    }
    while (j <= end){
        temp[k++] = array[j++];
    }
    for(i = 0; i < k; i++)
    {
        array[start + i] = temp[i];
    }
    return 0;
}
