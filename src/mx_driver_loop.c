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

void mx_driver_loop(t_global_environment *gv) {
    t_eval_result res = NULL;
    bool status = 1;

    while(status) {
        if (isatty(0)) {
            mx_print_prompt();
            mx_read_input(gv);
        }
        else {
            read_from_pipe(gv);
            status = 0;
        } 
        res = mx_eval(gv->str, gv, NULL, NULL);
        mx_strdel(&gv->str);
        mx_delete_evalresult(&res);
    }
}
