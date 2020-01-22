//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

void mx_eval(t_global_environment *gv, char *line) {
    gv->a = 1;
    mx_printstr("Hello there! ");
    mx_printstr(line);
    mx_printstr("\n");
}
