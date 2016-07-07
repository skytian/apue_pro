/*************************************************************************
    > File Name: g_shell_test.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Thu 07 Jul 2016 03:17:12 PM CST
 ************************************************************************/

#include<stdio.h>
#include<glib.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char *argv[]) {
	char *cl = "ls -l";
	if(g_shell_parse_argv(cl,&argc,&argv,NULL) < 0) {
		g_printf("can't parse shell\n");
	}
	g_printf("parse shell success\n");
	execvp(argv[0], argv);
}

