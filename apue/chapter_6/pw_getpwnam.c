#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>

struct passwd *getpwnam(const char *name) {
    struct passwd *ptr;

    setpwent();//if other process open the passwd file,offset the file to begining
    while( (ptr = getpwent()) != NULL)
        if(strcmp(name, ptr->pw_name) == 0)
            break;
    endpwent();
    return(ptr);
}

int main(int argc , char *argv[]) {
   struct passwd *ppasswd;
   ppasswd = getpwnam(argv[1]);
   printf("passwd name:%s passwd password:%s passwd uid:%d  passwd gid:%d passwd gecos:%s passwd dir:%s\n", ppasswd->pw_name,  ppasswd->pw_passwd, ppasswd->pw_uid, ppasswd->pw_gid, ppasswd->pw_gecos, ppasswd->pw_dir);
}
