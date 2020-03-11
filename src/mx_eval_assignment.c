//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----- Static Functions
static t_exp _assignment_variable(t_exp exp) {
    char *car = NULL;
    car = mx_left_exp(exp, "=");
    if (!mx_is_valid_parname(car)) {
        mx_strdel(&car);
        car = NULL;
    }
    return car;
}

static t_exp _assignment_value(t_exp exp) {
    char *cdr = mx_right_exp(exp, "=");
    char *first_word = mx_first_word(cdr); // take the first word to left from '='
    mx_strdel(&cdr);
    return first_word;
}

static t_exp _words_after_assignment(t_exp exp) {
    char *cdr = mx_right_exp(exp, "=");
    char *rest_words = mx_rest_words(cdr); // take the rest words to left from
    // '='
    mx_strdel(&cdr);
    return rest_words;
}


// ----    API Function
t_eval_result mx_eval_assignment(t_exp exp, t_global_environment *gv) {
    t_eval_result result = NULL;
    t_exp assignment_variable = _assignment_variable(exp);
    if (assignment_variable == NULL) { // если есть ошибка в имени переменной
        result = mx_simple_command(exp, gv, NULL, NULL);
    }
    else { // обрабатываем присвоение
        t_exp assignment_value = _assignment_value(exp);
        // save variable
        mx_env_set_var(assignment_variable, assignment_value, &(gv->vars));
        // check if other words
        t_exp words_after_assign = _words_after_assignment(exp);
        if (words_after_assign != NULL) {
            result = mx_eval(words_after_assign, gv, NULL, NULL);
        }
        else { // присвоение нормально, и нет слово после
            result = mx_new_evalresult();
        }
        mx_strdel(&words_after_assign);
        mx_strdel(&assignment_value);
    }
    mx_strdel(&assignment_variable);
    return result;
}


