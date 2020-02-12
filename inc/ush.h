#ifndef USH_H
#define USH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libmx.h"
#include "liststr.h"
#include "environment.h"

typedef struct global_environment {
    t_environment *env;
	char **envList;
	char **args;
	char *buffer;
	char *path;
	char *fullPath;
	char *shellName;
	unsigned int lineCounter;
	int errorStatus;

	char *str;   //reading line
	char buff[5];
	unsigned int cursor;
	
	char *history[500];
	unsigned int his_point;
	unsigned int show_his;
} t_global_environment;

typedef struct config {
    char **agv;
    int agvsize;
    t_global_environment *gv;
} t_config;

typedef struct builtInCommands {
	char *command;
	void (*func)(t_config *);
} t_pair_cmd_name;

void mx_init_shell(t_global_environment *gv);
void mx_driver_loop(t_global_environment *gv);
void mx_free_all(t_global_environment *gv);
void mx_print_prompt(void);

// TODO: delete later
#include "p.h"
#include "i.h"
#include "o.h"

#endif

