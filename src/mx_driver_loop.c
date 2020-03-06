#include "ush.h"

static void read_from_pipe(t_global_environment *gv) {
    char buffer[1024] = {'\0'};
    ssize_t size;
  
    size = read(0, buffer, sizeof(buffer));
    if (size < 257) {
        gv->str = strdup(buffer);
    }
    else {
        mx_printerr("u$h: file name too long: ");
        mx_printerr(buffer);
    }
}

static void read_from_stdin(t_global_environment *gv) {
    mx_set_input_mode();
    mx_print_prompt();
    mx_read_input(gv);
    mx_reset_input_mode();
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

void mx_driver_loop(t_global_environment *gv) {
    t_eval_result res = NULL;
    bool status = 1;
    int fd = -1;

    while(status) {
        if (isatty(0))
            read_from_stdin(gv);
        else {
            read_from_pipe(gv);
            status = 0;
        }
        fd = dup(0);
        res = mx_eval(gv->str, gv, NULL, NULL);
        if (!isatty(0) && fd != -1 && fd != 0) {
            dup2(fd, 0);
            close(fd);
        }
        mx_strdel(&gv->str);
        mx_delete_evalresult(&res);
    }
}
        //system("leaks -q ush");
