#include "ush.h"

void mx_builtin_export(t_config *cnf) {
    mx_printstr("export: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_unset(t_config *cnf) {
    mx_printstr("unset: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_fg(t_config *cnf) {
    mx_printstr("fg: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_exit(t_config *cnf) {
    mx_printstr("exit: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_env(t_config *cnf) {
    mx_printstr("env: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_cd(t_config *cnf) {
    mx_printstr("cd: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_pwd(t_config *cnf) {
    mx_printstr("pwd: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_which(t_config *cnf) {
    mx_printstr("which: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_echo(t_config *cnf) {
    mx_printstr("echo: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_alias(t_config *cnf) {
    mx_printstr("alias: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

