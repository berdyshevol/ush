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

int mx_builtin_export(t_global_environment *gv) {
    extern char **environ;

    if (gv->cnf->agv[1])
        for (int i = 1; gv->cnf->agv[i] != NULL; i++)
            putenv(gv->cnf->agv[i]);
    else {
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
    return EXIT_SUCCESS;
}
