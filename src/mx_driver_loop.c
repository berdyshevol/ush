//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

void mx_driver_loop(t_global_environment *gv) {
    char *line = NULL;

    while(1) {
        mx_print_prompt();
        line = mx_read_input();
        mx_eval(gv, line);
        mx_output();
        mx_strdel(&line);
    }
}
