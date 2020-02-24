#include "ush.h"

t_global_environment *mx_new_global_env(void) {
    t_global_environment *gv = malloc(sizeof(t_global_environment));
    //if (gv->shellName != NULL) free(gv->shellName);
    gv->shellName = "brothers' shell";
    gv->pwd = mx_strdup(getenv("PWD"));
    gv->oldpwd = mx_strdup(getenv("OLDPWD"));
    gv->his_point = 0;
    gv->show_his = 0;
    gv->bufsize = 128;
    gv->full_tmp_str = false;
    gv->backcpase_his = false;
    for (int i = 0; i < 500; i++)
        gv->history[i] = NULL;
    gv->tmp_str = NULL;
    return gv;
}
