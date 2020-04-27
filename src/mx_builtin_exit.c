#include "ush.h"

int mx_builtin_exit(t_global_environment *gv) {
    // system("leaks -q ush");
    if (gv->cnf->agv[1] == NULL)
        exit(0);
    if (gv->cnf->agvsize > 2) {
        fprintf(stderr, "exit: too many arguments\n");
        exit(255);
    }
    for (int i = 0; gv->cnf->agv[1][i]; i++)
        if (!mx_isdigit(gv->cnf->agv[1][i])) {
            fprintf(stderr, "exit: %s: numeric argument required\n",
                    gv->cnf->agv[1]);
            exit(255);
        }
    exit(mx_atoi(gv->cnf->agv[1]));
}
