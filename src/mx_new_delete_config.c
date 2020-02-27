//
// Created by Oleg Berdyshev on 2/7/20.
//
#include "evaluator.h"

t_config *mx_new_config(char **argv, int argc, bool fork_process) {
    t_config *cnf = malloc(sizeof (t_config));
    cnf->agv = argv;
    cnf->agvsize = argc;
    cnf->for_process = fork_process;
    return cnf;
}

void mx_delete_config(t_config **cnf) {
    if (cnf == NULL || *cnf == NULL)
        return;
//    if ((*cnf)->agv != NULL)
//        mx_delete_strvector(&((*cnf)->agv), &((*cnf)->agvsize));
    free(*cnf);
    *cnf = NULL;
}
