#include "ush.h"

void mx_builtin_export(t_config *cnf) {
    printf("export: %s", cnf->gv->shellName);
}

void mx_builtin_unset(t_config *cnf) {
    printf("unset: %s", cnf->gv->shellName);
}

void mx_builtin_fg(t_config *cnf) {
    printf("fg: %s", cnf->gv->shellName);
}

void mx_builtin_exit(t_config *cnf) {
    printf("exit: %s", cnf->gv->shellName);
}

void mx_builtin_env(t_config *cnf) {
    printf("unv: %s", cnf->gv->shellName);
}

void mx_builtin_cd(t_config *cnf) {
    printf("cd: %s", cnf->gv->shellName);
}

void mx_builtin_pwd(t_config *cnf) {
    printf("pwd: %s", cnf->gv->shellName);
}

void mx_builtin_which(t_config *cnf) {
    printf("export: %s", cnf->gv->shellName);
}

void mx_builtin_echo(t_config *cnf) {
    printf("export: %s", cnf->gv->shellName);
}

void mx_alias(t_config *cnf) {
    printf("alias: %s", cnf->gv->shellName);
}

