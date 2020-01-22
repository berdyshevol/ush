#ifndef ULH_H
#define ULH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "libmx.h"

typedef struct global_environment {
    int a; // TODO: delete
} t_global_environment;

void mx_init_shell(t_global_environment *gv);
void mx_driver_loop(t_global_environment *gv);
void mx_free_all(t_global_environment *gv);
void mx_print_prompt(void);

// TODO: delete later
#include "p.h"
#include "i.h"
#include "o.h"

#endif

