#include "ush.h"

static void path_with_hash(char **arr, char *dir, char **res, char *str) {
    mx_del_strarr(&arr);
    if (dir[0] == '/' && dir[1] != '/')
        *res = mx_strdup(dir);
    else if (dir[0] == '/' && dir[1] == '/')
        *res = mx_strdup("/");
    else
        *res = mx_strdup(str);
}

static char *path_finding(t_global_environment *gv, char *dir) {
    char str[1024];
    char **arr = NULL;
    char *res = NULL;
    int flag = 0;

    if (dir[0] == '/' && dir[1] != '/')
        sprintf(str, "%s", dir);
    else
        sprintf(str, "%s/%s", gv->pwd, dir);
    arr = mx_strsplit(str, '/');
    for (int i = 0; arr[i] != NULL; i++)
        if ((mx_strcmp(arr[i], "..") == 0) || (mx_strcmp(arr[i], ".") == 0)) {
            res = mx_path_cancat(arr, mx_strdup(str));
            flag = 1;
            break;
        }
    if (!flag)
        path_with_hash(arr, dir, &res, str);
    return res;
}

int mx_builtin_cd(t_global_environment *gv) {
    bool *flags = mx_flags_map(3);
    int status;
    char *dir_to_check = NULL;
    char *dir = NULL;

    if (!(dir_to_check = mx_flags_handler_cd(gv->cnf->agv, &flags, gv))) {
        free(flags);
        return EXIT_FAILURE;
    }
    dir = path_finding(gv, dir_to_check);
    mx_flags_settings_cd(gv, flags, &status, dir);
    mx_strdel(&dir_to_check);
    mx_strdel(&dir);
    free(flags);
    return status;
}
