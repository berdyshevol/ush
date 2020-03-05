#include "ush.h"

// ----------- UNSET builtin function -----------

int mx_builtin_unset(t_global_environment *gv) { // TODO: Доделать Unset and Export
    unsetenv(gv->cnf->agv[1]);
    return EXIT_SUCCESS;
}


// ----------- EXIT builtin function -----------

int mx_builtin_exit(t_global_environment *gv) {
    system("leaks -q ush");
    if (gv->cnf->agv[1] == NULL)
        exit(0);
    if (gv->cnf->agvsize > 1) {
        fprintf(stderr, "exit: too many arguments\n");
        exit(255);
    }
    for (int i = 0; gv->cnf->agv[1][i]; i++)
        if(!mx_isdigit(gv->cnf->agv[1][i])) {
            fprintf(stderr, "exit: %s: numeric argument required\n",
                    gv->cnf->agv[1]);
            exit(255);
        }
    exit(mx_atoi(gv->cnf->agv[1]));
}

int mx_alias(t_global_environment *gv) {
    mx_printstr("alias: ");
    mx_printstr(gv->shellName);
    mx_printstr("\n");
    return EXIT_SUCCESS;
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
