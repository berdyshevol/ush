//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----    API Function
void mx_list_of_values(t_list_of_values **list,
                       t_exp exps, t_global_environment *gv) {
    if (mx_is_last_word(exps)) {
        return; // end of list
    }
    else {
        t_exp first_word = mx_first_word(exps);
        t_eval_result eval_first_result = mx_eval_remove_escquotedquote(
                first_word);
        t_exp rest_words = NULL;

        if (eval_first_result->text != NULL)
            mx_liststr_push_back(list, eval_first_result->text, NULL);
        rest_words = mx_rest_words(exps);
        mx_list_of_values(list, rest_words, gv);

        mx_strdel(&rest_words);
        mx_delete_evalresult(&eval_first_result);
        mx_strdel(&first_word);
    }
}
