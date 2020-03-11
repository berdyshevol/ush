//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----    API Function
// Sequences
/**
 * Sequences is a sequences of:
 * lists (delimiter is: ; &)
 * pipeline ( delimiter: is | )
 * of words (delimiter is space)
 */
t_eval_result mx_eval_sequence(t_exp exps, t_global_environment *gv) {
    t_eval_result result = NULL;
    char *delim = ";";
    if (mx_is_last_exp(exps, delim)) {
        char *first_exp = mx_first_exp(exps, delim);
        result = mx_eval(first_exp, gv, NULL, NULL);
        mx_strdel(&first_exp);
    }
    else {
        char *first_exp = mx_first_exp(exps, delim);
        t_eval_result eval_fe = mx_eval(first_exp, gv, NULL, NULL);
        char *rest_exps = mx_rest_exps(exps, delim);
        result = mx_eval_sequence(rest_exps, gv);

        mx_strdel(&rest_exps);
        mx_delete_evalresult(&eval_fe);
        mx_strdel(&first_exp);
    }
    return result; // TODO: не знаю что вернуть
}

// for evaluating sequence of expressions
bool mx_is_last_exp(t_exp seq, char *op_name) {
    char *cdr = mx_right_exp(seq, op_name);
    bool return_value = cdr == NULL;
    free(cdr);
    return return_value;
}

t_exp mx_first_exp(t_exp seq, char *op_name) {
    char *car = mx_left_exp(seq, op_name);
    return car;
}

t_exp mx_rest_exps(t_exp seq, char *op_name) {
    char *cdr = mx_right_exp(seq, op_name);
    return cdr;
}
