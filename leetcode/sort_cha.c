#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct kv_t{
    int key;
    char value;
} t_kv;
char* frequencySort(char* s) {
    printf("s:%s\n", s);
    int num = 'z' -'A'+1;
    t_kv *cha = (t_kv *) malloc(sizeof(t_kv)*num);
    int count = 0;
    int i = 0, j;
    int k = 0;
    int key;
    char value;
    memset(cha, 0, sizeof(t_kv)*num);
    printf("s:%s\n", s);
    while(s[i] != '\0'){
        cha[s[i] - 'A'].key = cha[s[i] - 'A'].key + 1;
        cha[s[i] - 'A'].value = s[i];
        printf("s[i]- 'A':%d,cha[s[i] - 'A'].key:%d, cha[s[i] - 'A'].value:%c\n",s[i]-'A', cha[s[i]-'A'].key, cha[s[i]-'A'].value);
        i++;
        count++;
    }
    printf("s:%s\n", s);
    for(i = 0; i < num-1; i++){
        for(j = 0; j < num-1; j++){
            if(cha[j+1].key > cha[j].key){
                key = cha[j].key;
                value = cha[j].value;
                cha[j].key = cha[j+1].key;
                cha[j].value = cha[j+1].value;
                cha[j+1].key = key;
                cha[j+1].value = value;
                printf("cha.key:%d cha.value:%c\n", cha[j].key,cha[j].value);
            }
        }
    }
    printf("s:%s\n", s);

    char *re_char= (char *)malloc(count);
    for(i = 0; i < num; i++){
        if((j = cha[i].key) ==0)
            break;
        while(j--){
            re_char[k++] = cha[i].value;
        }
    }
    re_char[k] = '\0';
    printf("re_char:%s\n", re_char);
    free(cha);
    return re_char;

}

int main(int argc, char *argv[]){
    printf("%s\n", argv[1]);
    char *ch = frequencySort(argv[1]);
    printf("%s\n", ch);
    free(ch);
}
