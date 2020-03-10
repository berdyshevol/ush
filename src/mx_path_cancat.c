#include "ush.h"

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

static void cancat_dot_dotdot(char **temp, char ***arr, int *i) {
    mx_strdel(temp);
    if (mx_strcmp((*arr)[*i], ".") == 0) {
        *temp = dot_cancat(*arr, *i);
        (*i)--;
    }
    else {
        *temp = dotdot_cancat(*arr, *i);
        *i -= 2;
    }
    mx_del_strarr(arr);
    *arr = mx_strsplit(*temp, '/');
}

char *mx_path_cancat(char **arr, char *str) {
    char *temp = str;

    if (arr != NULL) {
        for (int i = 0; arr[i] != NULL; i++) {
            if (mx_strcmp(arr[0], "..") == 0 || mx_strcmp(arr[0], "." ) == 0) {
                mx_strdel(&temp);
                temp = mx_strdup("/");
                break;
            }
            if (mx_strcmp(arr[i], ".") == 0 || mx_strcmp(arr[i], "..") == 0) {
                cancat_dot_dotdot(&temp, &arr, &i);
                if (arr == NULL)
                    break;
            }
        }
    }
    if (arr)
        mx_del_strarr(&arr);
    return temp;
}
