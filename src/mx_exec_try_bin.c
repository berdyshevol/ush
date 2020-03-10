#include "ush.h"

static int mx_wexitstatud(int x);
static void exec_child(char *cmd, t_global_environment *gv);

// ----    API Function
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

void mx_apply_pipe_to_proc(int fd_out, int fd_in, t_global_environment *gv) {
    if (gv->cnf->pipe_fd[fd_out] != fd_out) {
        dup2(gv->cnf->pipe_fd[fd_out], fd_out);
        close(gv->cnf->pipe_fd[fd_out]);
    }
    close(gv->cnf->pipe_fd[fd_in]);
}

bool mx_try_bin(char *cmd, t_eval_result result, t_global_environment *gv) {
    int pid;

    switch (pid = fork()) {
        case -1:
            perror ("fork");
            break;
        case 0:
            if (mx_has_pipe(gv->cnf->pipe_fd))
                mx_apply_pipe_to_proc(1, 0, gv);
            exec_child(cmd, gv);
            break;
        default:
            if (mx_has_pipe(gv->cnf->pipe_fd))
                mx_apply_pipe_to_proc(0, 1, gv);
            mx_smart_wait(pid, result, gv);
            break;
    }
    return true;
}

// ----- Static Functions
static void exec_child(char *cmd, t_global_environment *gv) {
//    extern char **environ;

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

static int mx_wexitstatud(int x) {
    return x >> 8;
}

