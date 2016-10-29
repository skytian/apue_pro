#include<dirent.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2)
        printf("please input a directory name!\n");
    if((dp = opendir(argv[1])) == NULL )
        printf("error:can't open directory:%s\n", argv[1]);
    while((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
    exit(0);

}
