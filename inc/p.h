//
// Created by Oleg Berdyshev on 1/22/20.
//

#ifndef P_H
#define P_H

#include "ush.h"
// TODO: эти все функции лежат в mx_builtins.c. их позже можно разбить на разные файлы
void mx_builtin_export(t_config *cf);
void mx_builtin_unset(t_config *cf);
void mx_builtin_fg(t_config *cf);
void mx_builtin_exit(t_config *cf);
void mx_builtin_env(t_config *cf);
void mx_builtin_cd(t_config *cf);
void mx_builtin_pwd(t_config *cf);
void mx_builtin_which(t_config *cf);
void mx_builtin_echo(t_config *cf);
void mx_alias(t_config *cf);

#endif //USH_P_H
