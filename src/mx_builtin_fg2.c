#include "ush.h"

void mx_continue_process(int *st, t_stoped *ps, t_global_environment *g) {
    char *str = ps->str;
    pid_t pid = ps->pid;
    int n = ps->n;
    pid_t ppid = getpid();

    if (kill(-pid, SIGCONT))
        fprintf(stderr, "fg: %s\n", strerror(errno));
    printf("\x1b[1K\r\x1b[2K[%d] %d continued %s\n", n, pid, str);
    tcsetpgrp(STDIN_FILENO, pid);
    tcsetpgrp(STDOUT_FILENO, pid);
    waitpid(pid, st, WUNTRACED);
    if (WIFSTOPPED(*st))
        printf("\x1b[1K\r\x1b[2K[%d] %d suspended  %s\n", n, pid, str);
    else {
        mx_strdel(&ps->str);
        ps->pid = 0;
        g->count_jobs--;
    }
    tcsetpgrp(STDIN_FILENO, ppid);
    tcsetpgrp(STDOUT_FILENO, ppid);
}
