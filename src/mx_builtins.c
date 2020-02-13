#include "ush.h"

// ----------- UNSET builtin function -----------

int mx_builtin_unset(t_global_environment *gv) {
    unsetenv(gv->cnf->agv[1]);
    return EXIT_SUCCESS;
}

// ----------- FG builtin function ----------- Not done

int mx_builtin_fg(t_global_environment *gv) {
    mx_printstr("fg: ");
    mx_printstr(gv->shellName);
    mx_printstr("\n");
    return EXIT_SUCCESS;
}

// ----------- EXIT builtin function -----------

int mx_builtin_exit(t_global_environment *gv) {
    if (gv->cnf->agv[1] == NULL)
        exit(0);
    else
        exit(mx_atoi(gv->cnf->agv[1]));
}

// ----------- ENV builtin function ----------- Not done

int mx_builtin_env(t_global_environment *gv) {
    mx_printstr("env: ");
    mx_printstr(gv->shellName);
    mx_printstr("\n");
    return EXIT_SUCCESS;
}

int mx_builtin_which(t_global_environment *gv) {
    mx_printstr("which: ");
    mx_printstr(gv->shellName);
    mx_printstr("\n");
    return EXIT_SUCCESS;
}

int mx_alias(t_global_environment *gv) {
    mx_printstr("alias: ");
    mx_printstr(gv->shellName);
    mx_printstr("\n");
    return EXIT_SUCCESS;
}

