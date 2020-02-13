//
// Created by Oleg Berdyshev on 1/22/20.
//
#include "ush.h"

t_global_environment *mx_new_global_env(void) {
    t_global_environment *gv = malloc(sizeof(t_global_environment));
    //if (gv->shellName != NULL) free(gv->shellName);
    gv->shellName = "brothers' shell";
    gv->pwd = mx_strdup(getenv("PWD"));
    gv->oldpwd = mx_strdup(getenv("OLDPWD"));
    return gv;
}
