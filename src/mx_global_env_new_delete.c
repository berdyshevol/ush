//
// Created by Oleg Berdyshev on 1/22/20.
//
#include "ush.h"

t_global_environment *mx_new_global_env(void) {
    t_global_environment *gv = malloc(sizeof(t_global_environment));
    gv->shellName = "brothers' shell";
    gv->prompt = "u$h> ";
    gv->vars = mx_env_new();
    gv->functions = mx_env_new();
    gv->alias = mx_env_new();
    gv->cnf = NULL;
    return gv;
}

void mx_delete_global_env(t_global_environment **gv) {
    if (gv == NULL)
        return ;
    if (*gv == NULL)
        return ;
    mx_env_delete(&((*gv)->vars));
    mx_env_delete(&((*gv)->functions));
    mx_env_delete(&((*gv)->alias));
//    if ((*gv)->cnf != NULL)
//        mx_delete_config(&((*gv)->cnf));
    free(*gv);
    *gv = NULL;
}
