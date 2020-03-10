#include "ush.h"

int mx_builtin_unset(t_global_environment *gv) { // TODO: Доделать Unset and Export
    int res = EXIT_SUCCESS;

    if (gv->cnf->agvsize < 2) {
        fprintf(stderr, "unset: not enough arguments\n");
        return EXIT_FAILURE;
    }
    for (int i = 1; gv->cnf->agv[i] != NULL; i++) {
        if (unsetenv(gv->cnf->agv[i]) != -1
            && mx_match_search(gv->cnf->agv[i], MX_UNSET_ARG))
                mx_env_del_var(gv->cnf->agv[i], &gv->vars);
        else {
            fprintf(stderr, "unset: %s: invalid parameter name\n",
                    gv->cnf->agv[i]);
            res = EXIT_FAILURE;
        }
    }
    return res;
}

int mx_yes(t_global_environment *gv) {
        if (gv->cnf->agvsize > 1)
            while (1)
                puts(gv->cnf->agv[1]);
        else
            while (1)
                puts("y");
}

int mx_true(t_global_environment *gv) {
    if (gv)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int mx_false(t_global_environment *gv) {
    if (gv)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int mx_builtin_set(t_global_environment *gv) {
    for (t_environment *i = gv->vars; i != NULL; i = i->next)
        printf("%s=%s\n", i->key, i->value);
    return 0;
}
