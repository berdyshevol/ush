#include "ush.h"

void mx_builtin_export(t_config *cf) {
    printf("export: %s")
}
void mx_builtin_unset(t_config *cf) {}
void mx_builtin_fg(t_config *cf) {}
void mx_builtin_exit(t_config *cf) {}
void mx_builtin_env(t_config *cf) {}
void mx_builtin_cd(t_config *cf) {}
void mx_builtin_pwd(t_config *cf);
void mx_builtin_which(t_config *cf);
void mx_builtin_echo(t_config *cf);
void mx_alias(t_config *cf);
