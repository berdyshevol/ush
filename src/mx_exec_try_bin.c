//
// Created by Oleg Berdyshev on 2/7/20.
//

#include "ush.h"

int mx_wexitstatud(int x) {
    return x >> 8;
}

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv,
                t_redirect *redir) {
    int pid;
    int status;

    switch (pid = fork()) {
        case -1:
            perror ("fork");
            break;
        case 0:
            //mx_apply_redirect(redir);
            execvp(cmd, gv->cnf->agv);
            mx_printerr(gv->prompt);
            mx_printerr("command not found: ");
            mx_printerr(cmd);
            mx_printerr("\n");
            exit(1);
            break;
        default:
            waitpid (pid, &status, 0);
            //printf("ls -> %d", mx_wexitstatud(status));
            mx_env_set_var("?", mx_itoa(mx_wexitstatud(status)), &(gv->vars));
            result->status = mx_wexitstatud(status) == 0 ? true : false;
            break;
    }
    return true;
}
