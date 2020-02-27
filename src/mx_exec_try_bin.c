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



void mx_exec_child(char *cmd, t_eval_result result, t_global_environment *gv) {
    int pid = getpid();
    setgid(pid);
    mx_set_default_signals();
    printf("in child cmd=%s [0]=%d "
           "[1]=%d [2]=%d [3]=%d\n", cmd, gv->cnf->pipe_fd[0],
           gv->cnf->pipe_fd[1], gv->cnf->pipe_fd[2], gv->cnf->pipe_fd[3]);
    if (mx_apply_pipe(gv->cnf->pipe_fd)) {
        printf("after apply pipe cmd=%s [0]=%d "
               "[1]=%d [2]=%d [3]=%d\n", cmd, gv->cnf->pipe_fd[0],
               gv->cnf->pipe_fd[1], gv->cnf->pipe_fd[2], gv->cnf->pipe_fd[3]);
        int pid = fork();
        switch (pid) {
            case -1:
                perror ("fork");
                break;
            case 0:
                printf("forked again cmd=%s\n", cmd);
                execvp(cmd, gv->cnf->agv);
                break;
            default:
                mx_reset_pipefd(gv->cnf->pipe_fd);
                break;
        }
    }
    else if (mx_apply_redirect(gv->cnf->redirections)) {
        printf("in child in apply redir \n");
        execvp(cmd, gv->cnf->agv);
    }
    else if (execvp(cmd, gv->cnf->agv) == -1) {
        mx_printerr(gv->prompt);
        mx_printerr("command not found: ");
        mx_printerr(cmd);
        mx_printerr("\n");
        exit(127);
    }
}

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv,
                t_redirect *redir) {
    int pid;
    int status;
    printf("in shell cmd=%s\n", cmd);
    switch (pid = fork()) {
        case -1:
            perror ("fork");
            break;
        case 0:
            mx_exec_child(cmd, result, gv);
            break;
        default:
            waitpid (pid, &status, 0);
            mx_set_input_mode();
            mx_env_set_var("?", mx_itoa(mx_wexitstatud(status)), &(gv->vars));
            result->status = mx_wexitstatud(status) == 0 ? true : false;
            break;
    }
    return true;
}
