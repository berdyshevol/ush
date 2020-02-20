#include "ush.h"

void mx_driver_loop(t_global_environment *gv) {
    while(1) {
        mx_print_prompt();
        mx_read_input(gv);
        mx_eval(gv, gv->str);
        mx_output();
        mx_strdel(&gv->str);
    }
}
