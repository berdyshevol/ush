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

typedef struct {
    char *input;
    int input_fd;
    bool input_append;  // for << is true. If < then false
    int prev_input_fd;

    char *output;
    int output_fd;
    bool output_append; // for >> is true. If > then false
    int prev_output_fd;

    char *error;
    int error_fd;
    int prev_error_fd;
} t_redirect;

typedef struct config {
    char **agv;
    int agvsize;
    bool *new_proc; // NULL or false - dont fork builtin
    int *pipe_fd;
    t_redirect *redirections;
} t_config;

typedef struct global_environment {
    t_environment *vars;
    t_environment *functions;
    t_environment *alias;
    char *prompt;
    char **args;
    int argc;

    char *buffer;
    char *path;
    char *fullPath;
    char *shellName;
    unsigned int lineCounter;
    int errorStatus;
    char *pwd;
    char *oldpwd;
    t_config *cnf;
    
    char *str;
    char *tmp_str;
	char buff[5];
	unsigned int cursor;
    unsigned int bufsize;
	
	char *history[500];
	unsigned int his_point;
    unsigned int show_his;
    bool full_tmp_str;
    bool backcpase_his;
} t_global_environment;

typedef struct builtInCommands {
	char *name;
	int (*cmd)(t_global_environment *);
} t_pair_cmd_name;

typedef struct {
    char *text;
    bool status;
}* t_eval_result; // результат выполнения eval что есть статус
// выполнения pipeline должен быть int но пока что есть

#include "evaluator.h"

void mx_init_shell(t_global_environment **gv);
void mx_driver_loop(t_global_environment *gv);
void mx_free_all(t_global_environment *gv);
void mx_print_prompt(void);

// TODO: delete later
#include "p.h"
#include "i.h"
#include "o.h"


// это пашины
bool mx_cmp_name(void *data1, void *data2);
void mx_sort_arr(char **arr, bool (*cmp)(void *, void*));

// TODO: эти все функции лежат в mx_builtins.c. их позже можно разбить на
//  разные файлы
int mx_builtin_export(t_global_environment *gv);
int mx_builtin_unset(t_global_environment *gv);
int mx_builtin_fg(t_global_environment *gv);
int mx_builtin_exit(t_global_environment *gv);
int mx_builtin_env(t_global_environment *gv);
int mx_builtin_cd(t_global_environment *gv);
int mx_builtin_pwd(t_global_environment *gv);
int mx_builtin_which(t_global_environment *gv);
int mx_builtin_echo(t_global_environment *gv);
int mx_alias(t_global_environment *gv);

t_global_environment *mx_new_global_env(void);
void mx_delete_global_env(t_global_environment **gv);
t_config *mx_config_new();
void mx_delete_config(t_config **cnf);

t_eval_result mx_execute(char *command, t_global_environment *gv);

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv);

bool try_builtin(char *cmd, t_eval_result result, t_global_environment *gv);
void mx_run_builtin(int id, t_eval_result result, t_global_environment *gv);

// pipe
int *mx_pipe_fd_new();
void mx_pipe_fd_delete(int **pipe_fd);
void mx_smart_close_fd(int *fd, int std);
int mx_fd_is_valid(int fd);
bool mx_apply_pipe(int *pipe_fd);
bool mx_has_pipe(int *pipe_fd);
void mx_reset_pipefd(int *pipe_fd);

//
int mx_wexitstatud(int x);

#endif

