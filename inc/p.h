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
#include "libmx.h"


// TODO: эти все функции лежат в mx_builtins.c. их позже можно разбить на разные файлы
void mx_builtin_export(t_config *cf);
void mx_builtin_unset(t_config *cf);
void mx_builtin_fg(t_config *cf);
void mx_builtin_exit(t_config *cf);
void mx_builtin_env(t_config *cf);
void mx_builtin_cd(t_config *cf);
void mx_builtin_pwd();
void mx_builtin_which(t_config *cf);
void mx_builtin_echo(t_config *cf);
void mx_alias(t_config *cf);

void mx_sort_arr(char **arr, bool (*cmp)(void *, void*));
bool mx_cmp_name(void *data1, void *data2);

#endif //USH_P_H
