#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <setjmp.h>
#include <errno.h>

#define MAXLINE 1024
void pr_exit(int status);
void err_sys(const char *buf);
void pr_mask(const char *str);
