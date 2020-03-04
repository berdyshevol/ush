//
// Created by Oleg Berdyshev on 2/7/20.
//
#include "evaluator.h"

// это вспомогательная структура для пердачи параметров по копиии
// все внетреннии указатели нужно отдельно free. Мы не free в delete
t_config *mx_config_new() {
    t_config *cnf = malloc(sizeof (t_config));
    cnf->agv = NULL;
    cnf->agvsize = 0;
    cnf->new_proc = NULL;
    cnf->pipe_fd = NULL;
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
