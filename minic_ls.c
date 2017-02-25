#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    DIR *p_dir;
    struct dirent *dirp;

    if(argc != 2) {
        printf("useage: ls directory name");
        exit(1);
    }

    if((p_dir = opendir(argv[1])) == NULL) {
        printf("read dir error!");
        exit(1);
    }

    while ((dirp = readdir(p_dir)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(p_dir);

    exit(0);


}
