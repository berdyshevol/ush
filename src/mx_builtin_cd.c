//
// Created by Pavlo Symonov on 2/7/20.
//

#include "ush.h"

static bool *flags_map();
static char *flags_handler_cd(char **argv, bool **is_flag);
static int open_or_not_catalog(char *dir, bool old);
static int open_oldpwd_catalog(t_global_environment *gv, char *str);
static int open_incoming_catalog(t_global_environment *gv, char *dir);
static char *open_link_markup(char *dir);
static char *path_finding(t_global_environment *gv, char *dir);
static char *path_cancat(char **arr, char *str);
static char *dotdot_cancat(char **arr, int i);
static char *dot_cancat(char **arr, int i);

int mx_builtin_cd(t_global_environment *gv) {
    bool *flags = flags_map();
    int status;
    char *dir_to_check = NULL;
    char *dir = NULL;

    if(!(dir_to_check = flags_handler_cd(gv->cnf->agv, &flags)))
        return EXIT_FAILURE;
    dir = path_finding(gv, dir_to_check);
    if (flags[FLAG_s]) {
        if (flags[FLAG_minus])
            if (open_or_not_catalog(gv->oldpwd, true) == EXIT_SUCCESS)
                status = open_oldpwd_catalog(gv, gv->oldpwd);
            else
                status = EXIT_FAILURE;
        else
            if (open_or_not_catalog(dir, false) == EXIT_SUCCESS)
                status = open_incoming_catalog(gv, dir);
            else
                status = EXIT_FAILURE;
    }
    else if (flags[FLAG_P]) {
        if (flags[FLAG_minus])
            status = open_oldpwd_catalog(gv, open_link_markup(gv->oldpwd));
        else
            status = open_incoming_catalog(gv, open_link_markup(dir));
    }
    else if (flags[FLAG_minus])
        status = open_oldpwd_catalog(gv, gv->oldpwd);
    else
        status = open_incoming_catalog(gv, dir);

    mx_strdel(&dir_to_check);
    mx_strdel(&dir);
    free(flags);
    // system("leaks -q ush");
    return status;
}

// ----------- CD builtin functions -----------

static bool *flags_map() {
    bool *res = (bool *) malloc(sizeof (bool) * 3);

    for (int i = 0; i < 3; i++)
        res[i] = false;
    return res;
}

static char *flags_handler_cd(char **argv, bool **is_flag) {
    for (int i = 1; argv[i] != NULL; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-' && argv[i][2] == '\0')
                return argv[i + 1] == NULL ? mx_strdup(getenv("HOME"))
                                           : mx_strdup(argv[i + 1]);
            else if (argv[i][1] == '\0')
                (*is_flag)[FLAG_minus] = true;
            else
                for (int j = 1; argv[i][j]; j++) {
                    if (argv[i][j] == 's')
                        (*is_flag)[FLAG_s] = true;
                    else if (argv[i][j] == 'P')
                        (*is_flag)[FLAG_P] = true;
                    else {
                        fprintf(stderr, "u$h: cd: -%c: invalid option\n",
                                argv[i][j]);
                        fprintf(stderr, "cd: usage: cd [-s|-P] [dir]\n");
                        return NULL;
                    }
                }
        }
        else
            return mx_strdup(argv[i]);
    }
    return mx_strdup(getenv("HOME"));
}

static int open_or_not_catalog(char *dir, bool old) {
    char link_read[PATH_MAX + 1];
    struct stat sb;

    lstat(dir, &sb);
    if (old) {
        if (mx_strcmp(dir, realpath(dir, link_read)) != 0) {
            fprintf(stderr, "cd: not a directory: %s\n", dir);
            return EXIT_FAILURE;
        }
    }
    else if (MX_ISLNK(sb.st_mode)) {
        fprintf(stderr, "cd: not a directory: %s\n", dir);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int open_oldpwd_catalog(t_global_environment *gv, char *dir) {
    chdir(dir);
    gv->oldpwd = gv->pwd;
    setenv("OLDPWD", gv->pwd, 1);
    gv->pwd = dir;
    setenv("PWD", dir, 1);
    if (strstr(dir, getenv("HOME")))
        puts(mx_replace_substr(dir, getenv("HOME"), "~"));
    else
        puts(dir);
    return EXIT_SUCCESS;
}

static int open_incoming_catalog(t_global_environment *gv, char *dir) {
    if (chdir(dir) != 0) {
        perror("cd");
        return EXIT_FAILURE;
    }
    else {
        mx_strdel(&gv->oldpwd);
        gv->oldpwd = mx_strdup(gv->pwd);
        setenv("OLDPWD", gv->pwd, 1);
        mx_strdel(&gv->pwd);
        gv->pwd = mx_strdup(dir);
        setenv("PWD", gv->pwd, 1);
    }
    return EXIT_SUCCESS;
}

static char *open_link_markup(char *dir) {
    char link_read[PATH_MAX + 1];

    return realpath(dir, link_read);;
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
            res = path_cancat(arr, mx_strdup(str));
            flag = 1;
            break;
        }
    if (!flag) {
        mx_del_strarr(&arr);
        if (dir[0] == '/' && dir[1] != '/')
            res = mx_strdup(dir);
        else if (dir[0] == '/' && dir[1] == '/')
            res = mx_strdup("/");
        else
            res = mx_strdup(str);
    }
    return res;
}

static char *path_cancat(char **arr, char *str) {
    char *temp = str;

    if (arr != NULL) {
        for (int i = 0; arr[i] != NULL; i++) {
            if (mx_strcmp(arr[0], "..") == 0 || mx_strcmp(arr[0], "." ) == 0) {
                mx_strdel(&temp);
                temp = mx_strdup("/");
                break;
            }
            if (mx_strcmp(arr[i], ".") == 0 || mx_strcmp(arr[i], "..") == 0) {
                mx_strdel(&temp);
                if (mx_strcmp(arr[i], ".") == 0) {
                    temp = dot_cancat(arr, i);
                    i--;
                }
                else {
                    temp = dotdot_cancat(arr, i);
                    i -= 2;
                }
                mx_del_strarr(&arr);
                arr = mx_strsplit(temp, '/');
                if (arr == NULL)
                    break;
            }
        }
    }
    if (arr)
        mx_del_strarr(&arr);
    return temp;
}

static char *dotdot_cancat(char **arr, int i) {
    char *temp = NULL;
    char *tmp = NULL;

    for (int j = 0; j < i - 1; j++) {
        tmp = mx_strjoin(temp, "/");
        mx_strdel(&temp);
        temp = mx_strjoin(tmp, arr[j]);;
        mx_strdel(&tmp);
    }
    for (int b = i + 1; arr[b] != NULL; b++) {
        tmp = mx_strjoin(temp, "/");
        mx_strdel(&temp);
        temp = mx_strjoin(tmp, arr[b]);;
        mx_strdel(&tmp);
    }
    return temp;
}

static char *dot_cancat(char **arr, int i) {
    char *temp = NULL;
    char *tmp = NULL;

    for (int j = 0; j < i; j++) {
        tmp = mx_strjoin(temp, "/");
        mx_strdel(&temp);
        temp = mx_strjoin(tmp, arr[j]);;
        mx_strdel(&tmp);
    }
    for (int b = i + 1; arr[b] != NULL; b++) {
        tmp = mx_strjoin(temp, "/");
        mx_strdel(&temp);
        temp = mx_strjoin(tmp, arr[b]);;
        mx_strdel(&tmp);
    }
    return temp;
}
