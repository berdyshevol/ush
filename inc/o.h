//
// Created by Oleg Berdyshev on 1/22/20.
//

#ifndef USH_O_H
#define USH_O_H

#include "ush.h"

t_global_environment *mx_new_global_env(void);
void mx_eval(t_global_environment *gv, char *line);
void mx_output(void);
int mx_is_closed_expression(char *s);

#endif //USH_O_H
