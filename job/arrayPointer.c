#include<stdio.h>
#include<string.h>

int main(){
    char str[] = "abcdbe";
    char strArr[3][3] = {{'a','b','c'},{'d','e','f'},{'g','h','i'}};
    char *ap[3] = {strArr[0],strArr[1],strArr[2]};
    char (*sp)[3] = strArr;
    int i = 0;
    char *p =  str;
    printf("str:%s\n",str);
    for(i = 0; i < strlen(str); i++){
        printf("str[%d]      :%c\n",i, str[i]);
        printf("*p          :%c\n",*p++);
        if(i < 3){
            printf("strArr[%d][0]:%c\n",i,*strArr[i]);
            printf("strArr[%d][1]:%c\n",i,*(strArr[i]+1));
            printf("strArr[%d][2]:%c\n",i,*(strArr[i]+2));
            printf("*ap[%d]      :%c\n",i, *ap[i]);
            printf("*(ap[%d]+1)  :%c\n",i, *(ap[i]+1));
            printf("*(ap[%d]+2)  :%c\n",i, *(ap[i]+2));
            printf("*(*(sp+%d)+0):%c\n",i, *(*(sp+i)+0));
            printf("*(*(sp+%d)+1):%c\n",i, *(*(sp+i)+1));
            printf("*(*(sp+%d)+2):%c\n",i, *(*(ap+i)+2));
        }
    }
}
