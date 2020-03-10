//
// Created by Oleg Berdyshev on 1/22/20.
//
#include "ush.h"

#ifndef P_H
#define P_H

#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <regex.h>
#include "libmx.h"

#define MX_IFMT          0170000
#define MX_IFLNK         0120000
#define MX_ISLNK(m)      (((m) & MX_IFMT) == MX_IFLNK)
#define MX_OK            (1<<0)  /* test for execute or search permission */
#define MX_EXPORT_REGEX "^[A-Za-z_]+[A-Za-z0-9_]*(=.*)?$"
#define MX_UNSET_ARG "^([0-9]+|[A-Za-z_]+[0-9A-Za-z_]*)$"
#define MX_ENV_I "^-(i*|i+.*|-.+)$"

typedef enum {
    CD_minus,
    CD_s,
    CD_P
}       e_cd_flags;

typedef enum {
    WH_a,
    WH_s
}       e_wh_flags;

// TODO: эти все функции лежат в mx_builtins.c. их позже можно разбить на разные файлы
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
int mx_yes(t_global_environment *gv);
int mx_false(t_global_environment *gv);
int mx_true(t_global_environment *gv);
int mx_set(t_global_environment *gv);

void mx_clearenv(void);
void mx_print_env(void);
char **mx_environ_copy(void);
void mx_putenv(char *var);
void mx_env_fill(char **src);
char *mx_get_env_name(char *var);
char *mx_get_env_value(char *var);
bool *mx_flags_map(int flags_num);
int mx_exec_env(char **arr, char *path);
bool mx_cmp_name(void *data1, void *data2);
int mx_match_search(char *str, char *regex);
char *mx_path_cancat(char **arr, char *str);
int mx_print_error_env(char ch, int err, char *str);
char *mx_flags_handler_cd(char **argv, bool **is_flag,
                          t_global_environment *gv);
void mx_sort_arr(char **arr, bool (*cmp)(void *, void*));
int mx_flags_handler_env(char **argv, int *i, char **path);
void mx_flags_settings_cd(t_global_environment *gv, bool *flags,
                          int *status, char *dir);
void mx_export_var_to_lists(char *arg, t_global_environment *gv);

#endif //USH_P_H
