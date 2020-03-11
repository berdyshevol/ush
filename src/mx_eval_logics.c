//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

static t_exp mx_if_predicate(t_exp exp);
static t_exp mx_if_consequent(t_exp exp);
static t_exp mx_if_alternative(t_exp exp);
static bool mx_result_of_if_predicate(t_exp exp, t_global_environment *gv);

// ----    API Functions
/**
 * a && b, if a ok then exec b
 * a || b  if b fail then exec b
 * @param exp
 * @return
 */
t_eval_result mx_eval_logic(t_exp exp, t_global_environment *gv) {
    t_eval_result res = NULL;

    if (mx_result_of_if_predicate(exp, gv) == true) {
        t_exp if_consequent = mx_if_consequent(exp);
        res = mx_eval(if_consequent, gv, NULL, NULL);
        mx_strdel(&if_consequent);
    }
    else {

        t_exp if_alternative = mx_if_alternative(exp);
        res = mx_eval(if_alternative, gv, NULL, NULL);
        mx_strdel(&if_alternative);
    }
    return res; // TODO: не знаю я прав или нет
}


// ----- Static Functions
// Conditionals && ||. zsh calls it sublist
static t_exp mx_if_predicate(t_exp exp) {
    char *op_name = mx_get_op_name(exp);
    char *car = mx_left_exp(exp, op_name);
    return car;
}

// for "&& pipeline"
static t_exp mx_if_consequent(t_exp exp) {
    char *cdr = mx_right_exp(exp, "&&");
    return cdr;
}

// for "|| pipeline"
static t_exp mx_if_alternative(t_exp exp) {
    char *cdr = mx_right_exp(exp, "||");
    return cdr;
}

static bool mx_result_of_if_predicate(t_exp exp, t_global_environment *gv) {
    bool return_result;
    t_exp if_predicate = mx_if_predicate(exp);
    t_eval_result result_if_predicate = mx_eval(if_predicate, gv, NULL, NULL);

    if (result_if_predicate == NULL)
        return_result = true;
    else
        return_result = (result_if_predicate->status == true);

    mx_delete_evalresult(&result_if_predicate);
    mx_strdel(&if_predicate);
    return return_result;
}

