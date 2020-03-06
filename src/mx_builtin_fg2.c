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
    if (MX_WIFSTOPPED(*st))
        printf("\x1b[1K\r\x1b[2K[%d] %d suspended  %s\n", n, pid, str);
    else {
        mx_strdel(&ps->str);
        ps->pid = 0;
        g->count_jobs--;
    }
    tcsetpgrp(STDIN_FILENO, ppid);
    tcsetpgrp(STDOUT_FILENO, ppid);
}

void mx_add_process_list(t_global_environment *gv, pid_t pid) {
    t_stoped *tmp = gv->jobs_list;

    while (tmp->next != NULL) {
        if (tmp->str == NULL) {
            tmp->pid = pid;
            tmp->str = strdup(gv->str);
            gv->last_stoped = tmp;
            printf("\n\r\x1b[2K[%d] %d suspended %s\n", tmp->n, pid, gv->str);
            return;
        }
        tmp = tmp->next;
    }
    if (tmp->next == NULL) {
        tmp->next = mx_add_empty_job(gv);
        tmp->pid = pid;
        tmp->str = strdup(gv->str);
        gv->last_stoped = tmp;
        printf("\n\r\x1b[2K[%d] %d suspended %s\n", tmp->n, pid, gv->str);
    }
}
