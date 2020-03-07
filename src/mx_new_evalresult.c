//
// Created by Oleg Berdyshev on 2/5/20.
//
#include "evaluator.h"

t_eval_result mx_new_evalresult(void) {
    t_eval_result eval_result = malloc(sizeof(t_eval_result));
    eval_result->text = NULL;
    eval_result->status = true;
    eval_result->exit_no = -1;
    return eval_result;
}

void mx_delete_evalresult(t_eval_result *eval_result) {
    if (eval_result == NULL || *eval_result == NULL)
        return;
    if ((*eval_result)->text != NULL)
        free((*eval_result)->text);
    free(*eval_result);
    *eval_result = NULL;
}
