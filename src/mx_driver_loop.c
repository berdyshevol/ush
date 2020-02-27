#include "ush.h"

void mx_driver_loop(t_global_environment *gv) {
    t_eval_result res = NULL;
    while(1) {
        mx_print_prompt();
        mx_read_input(gv);
        res = mx_eval(gv->str, gv, NULL, NULL);
        mx_output();
        mx_strdel(&gv->str);
        mx_delete_evalresult(&res);
    }
}
