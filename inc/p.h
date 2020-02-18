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

typedef enum {
    CD_minus,
    CD_s,
    CD_P,
} e_cd_flags;

typedef enum {
    WH_a,
    WH_s,
} e_wh_flags;

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

bool *flags_map(int flags_num);
void mx_sort_arr(char **arr, bool (*cmp)(void *, void*));
bool mx_cmp_name(void *data1, void *data2);

#endif //USH_P_H
