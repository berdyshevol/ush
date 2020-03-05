//
// Created by Oleg Berdyshev on 2/7/20.
//

#include "ush.h"

int mx_wexitstatud(int x) {
    return x >> 8;
}

void mx_set_default_signals() {
     mx_reset_input_mode();
     signal(SIGINT, SIG_DFL);
     signal(SIGQUIT, SIG_DFL);
     signal(SIGTSTP, SIG_DFL);
     signal(SIGTTIN, SIG_DFL);
     signal(SIGTTOU, SIG_DFL);
     signal(SIGCHLD, SIG_DFL);
}

void mx_print_nocmd(char *cmd, t_global_environment *gv) {
    mx_printerr(gv->prompt);
    mx_printerr("command not found: ");
    mx_printerr(cmd);
    mx_printerr("\n");
    exit(127);
}

void mx_exec_child(char *cmd, t_eval_result result, t_global_environment *gv) {
    int pid = getpid();
    setgid(pid);
    mx_set_default_signals();
//    if (mx_has_pipe(gv->cnf->pipe_fd)) {
//        int pid;
//        int status;
//        switch (pid = fork()) {
//            case -1:
//                perror("fork");
//                break;
//            case 0:
//                mx_apply_pipe(gv->cnf->pipe_fd);
//                if (execvp(cmd, gv->cnf->agv) < 0) {
//                    mx_print_nocmd(cmd, gv);
//                }
//                break;
//            default:
//                waitpid(pid, &status, 0);
//        }
//    }
//    else
    if (mx_apply_redirect(gv->cnf->redirections)) {
        if (execvp(cmd, gv->cnf->agv) <  0) {
            mx_print_nocmd(cmd, gv);
        }
        mx_reset_redirections(gv->cnf->redirections);
    }
    else if (execvp(cmd, gv->cnf->agv) < 0) {
        mx_print_nocmd(cmd, gv);
    }
    exit(0);
}

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv) {
    int pid;
    int status;

    switch (pid = fork()) {
        case -1:
            perror ("fork");
            break;
        case 0:
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[1] != 1) {
                    dup2(gv->cnf->pipe_fd[1], 1);
                    close(gv->cnf->pipe_fd[1]);
                }
                close(gv->cnf->pipe_fd[0]);
            }
            mx_exec_child(cmd, result, gv);
            break;
        default:
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[0] != 0) {
                    dup2(gv->cnf->pipe_fd[0], 0);
                    close(gv->cnf->pipe_fd[0]);
                }
                close(gv->cnf->pipe_fd[1]);
            }
            waitpid (pid, &status, 0);
            mx_set_input_mode();
            int i = mx_wexitstatud(status);
            char *itoa = mx_itoa(mx_wexitstatud(status));
            mx_env_set_var("?", itoa, &(gv->vars));
            result->status = mx_wexitstatud(status) == 0 ? true : false;
            mx_strdel(&itoa);
            break;
    }
    return true;
}
