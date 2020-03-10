#include "ush.h"

int mx_wexitstatud(int x) {
    return x >> 8;
}

void mx_print_nocmd(char *cmd) {
    mx_printerr("ush ");
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

static void exec_child(char *cmd, t_global_environment *gv) {
    if (isatty(STDIN_FILENO)){
        setegid(getpid());
        setpgid(getpid(), 0);
        tcsetpgrp(STDIN_FILENO, getpgrp());
        tcsetpgrp(STDOUT_FILENO, getpgrp());
    }
    if (mx_apply_redirect(gv->cnf->redirections)) {
        if (execvp(cmd, gv->cnf->agv) <  0) {
            mx_print_nocmd(cmd);
        }
        mx_reset_redirections(gv->cnf->redirections);
    }
    else if (execvp(cmd, gv->cnf->agv) < 0) {
        mx_print_nocmd(cmd);
    }
    exit(0);    
}

void mx_smart_wait(int pid, t_eval_result result, t_global_environment *gv) {
    int status;

    waitpid (pid, &status, WUNTRACED);
    if (MX_WIFSTOPPED(status)) {
        mx_add_process_list(gv, pid);
        if (gv != NULL)  //  I added !!!!!!!
            gv->count_jobs++;
    }
    char *itoa = mx_itoa(mx_wexitstatud(status));
    mx_env_set_var("?", itoa, &(gv->vars));
    result->status = mx_wexitstatud(status) == 0 ? true : false;
    result->exit_no = mx_wexitstatud(status);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    tcsetpgrp(STDOUT_FILENO, getpgrp());
    mx_strdel(&itoa);
}

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv) {
    int pid;

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
            exec_child(cmd, gv);
            break;
        default:
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[0] != 0) {
                    dup2(gv->cnf->pipe_fd[0], 0);
                    close(gv->cnf->pipe_fd[0]);
                }
                close(gv->cnf->pipe_fd[1]);
            }
            mx_smart_wait(pid, result, gv);
            break;
    }
    return true;
}
