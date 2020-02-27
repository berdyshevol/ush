//
// Created by Oleg Berdyshev on 2/7/20.
//
#include "evaluator.h"

// это вспомогательная структура для пердачи параметров по копиии
// все внетреннии указатели нужно отдельно free. Мы не free в delete
t_config *mx_config_new() {
    t_config *cnf = malloc(sizeof (t_config));
//    cnf->agv = argv;
//    cnf->agvsize = argc;
//    cnf->for_process = new_proc;
//    cnf->pipe_fd = pipe_fd;
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
