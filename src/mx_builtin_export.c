//
// Created by Pavlo Symonov on 2/7/20.
//

#include "ush.h"

static int name_compare(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2) && *s2 != '=') {
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 == '=')
        return 0;
    return *s1 - *s2;
}

int mx_match_search(char *str, char *regex) {
    regex_t reg;
    int res;

    regcomp(&reg, regex, REG_EXTENDED);
    res = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    return res == 0;
}

static char *mx_get_var_name(char *arg) {
    char **arr = mx_strsplit(arg, '=');
    char *res = mx_strdup(arr[0]);

    mx_del_strarr(&arr);
    return res;
}

static int exp_error_check(char *str) {
    char *name = mx_get_var_name(str);

    if (mx_match_search(str, "^[0-9]"))
        fprintf(stderr, "export: not an identifier: %s\n", name);
    else if (mx_match_search(str, "^[-+]"))
        fprintf(stderr, "export: does not accept any options: %c%c\n",
                str[0], str[1]);
    else
        fprintf(stderr, "export: not valid in this context: %s\n", name);
    mx_strdel(&name);
    return 1;
}

static void print_export_env(char **environ) {
    mx_sort_arr(environ, mx_cmp_name);
    for (int i = 0; environ[i] != NULL; i++) {
        if (name_compare("_", environ[i]) == 0)
            continue;
        else {
            mx_printstr(environ[i]);
            mx_printchar('\n');
        }
    }
}

int mx_builtin_export(t_global_environment *gv) {
    extern char **environ;
    int status = 0;

    if (gv->cnf->agv[1] == NULL) {
        print_export_env(environ);
    }
    else {
        for (int i = 1; gv->cnf->agv[i] != NULL; i++) {
            if (mx_match_search(gv->cnf->agv[i], MX_EXPORT_REGEX))
                putenv(gv->cnf->agv[i]);
            else
                status = exp_error_check(gv->cnf->agv[i]);
        }
    }
    return status;
}
