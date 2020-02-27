#include "ush.h"

int mx_wexitstatud(int x) {
    return x >> 8;
}

// void mx_set_default_signals() {
//     mx_reset_input_mode();
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
//     signal(SIGTSTP, SIG_DFL);
//     signal(SIGTTIN, SIG_DFL);
//     signal(SIGTTOU, SIG_DFL);
//     signal(SIGCHLD, SIG_DFL);
//  }

void mx_exec_child(char *cmd, t_eval_result result, t_global_environment *gv,
                    t_redirect *redir) {
    //MAKprintf("\nWORK!\n");
    // int pid = getpid();
    // setgid(pid);
    // printf("\nPID is %n\nGID is %n\n", pid, getgid);
    // mx_set_default_signals();
    mx_apply_redirect(redir);
    execvp(cmd, gv->cnf->agv);
    mx_printerr(gv->prompt);
    if (strlen(cmd) < 257) {
        mx_printerr("command not found: ");
        mx_printerr(cmd);
        mx_printerr("\n");
    }
    else {
        mx_printerr("file name too long: ");
        mx_printerr(cmd);
        mx_printerr("\n");
    }
    exit(127);
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
            mx_exec_child(cmd, result, gv, redir);
            break;
        default:
            waitpid (pid, &status, 0);
            //mx_set_input_mode();
            mx_env_set_var("?", mx_itoa(mx_wexitstatud(status)), &(gv->vars));
            result->status = mx_wexitstatud(status) == 0 ? true : false;
            break;
    }
    return true;
}
