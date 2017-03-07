/*************************************************************************
    > File Name: test_get_name.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Fri 02 Dec 2016 06:29:16 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int get_file_name(char *ftp_url,char *file_dir,char *server_ip)
{
    char *p_str1;
    char *p_str2;

    if((ftp_url == NULL)||(file_dir == NULL)||(server_ip == NULL))
    {
        return -1;
    }
    
    p_str1=strstr(ftp_url,"//");
    if((p_str1==NULL))
    {
        return -1;
    }
    
    p_str2=strstr(p_str1+2,":");
    if((p_str2 == NULL))
    {
        p_str2=strstr(p_str1+2,"/");
        if((p_str2 == NULL))
        {
            return -1;
        }
    }
        
    p_str2 = strstr(p_str2,"/");
    if(p_str2 == NULL)
    {
        return -1;
    }
    memcpy(server_ip,p_str1+2,p_str2-p_str1-5);
    sprintf(file_dir,"%s/",p_str2);

    //If the ftp server is a linux version, before the path without adding '/',but window version of needs
#if 1
    if(file_dir[0]=='/')
    {
        int len=strlen(file_dir);
        memmove(file_dir,file_dir+1,len-1);
        file_dir[len-1]='\0';
    }
#endif

    printf("from url=%s get server ip =%s dir name =%s\n",ftp_url,server_ip,file_dir);
    
    return 0;
}

int main(int argc, char *argv[]){
	char file_dir[64];
	char server_ip[64];
	char ftp_url[256];
	get_file_name(argv[1], file_dir, server_ip);
}
