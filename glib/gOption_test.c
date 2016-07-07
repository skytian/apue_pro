/*************************************************************************
    > File Name: gOption_test.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Thu 07 Jul 2016 08:17:41 AM CST
 ************************************************************************/


#include<stdio.h>
#include<glib.h>
#include<string.h>
#include<stdlib.h>

static gint testValue = 0;
static gint runValue = 0;

static GOptionEntry  options[] = {
	{"test", 't', 0,G_OPTION_ARG_INT, &testValue, "value of test", 0},
	{"run", 'r', 0,G_OPTION_ARG_INT, &runValue, "value of run", 0},
	{NULL}
};
int main(int argc, char *argv[]) {
	GOptionContext *context = NULL;
	GError *error = NULL;

	context = g_option_context_new("start init task");
	g_option_context_add_main_entries(context, options, NULL);

	if(g_option_context_parse(context, &argc, &argv, &error) == FALSE) {
		if(error != NULL) {
			g_printerr("%s\n", error->message);
			g_error_free(error);
		} else
			g_printerr("An unknown error occurred\n");
		exit(1);
	}

	g_option_context_free(context);

	g_print("Now value is : test= %d, run= %d \n", testValue, runValue);

	return 0;
}
