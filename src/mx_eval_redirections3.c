//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"

// ----- Static Functions

void _extract_input_helper(char *delim, bool append, char **exp,
                           t_redirect **redirect, bool *er) {
    char *right_exp;
    char *left_exp;
    char *after_redirect;
    char *input;
    char *tmp;

    left_exp = mx_left_exp(*exp, delim);
    right_exp = mx_right_exp(*exp, delim);
    input = mx_first_word(right_exp);
    after_redirect = mx_rest_words(right_exp);
    *er = mx_extract_helper(input, &((*redirect)->input), append, &((*redirect)
            ->input_append));
    if (*er) {
        tmp = mx_strjoin_with_space(left_exp, after_redirect);
        mx_strdel(exp);
        *exp = tmp;
    }
    mx_delete_arlere(&after_redirect, &left_exp, &right_exp);
}

void _extract_output_helper(char *delim, bool append, char **exp,
                            t_redirect **redirect, bool *er) {
    char *right_exp;
    char *left_exp;
    char *after_redirect;
    char *input;
    char *tmp;

    left_exp = mx_left_exp(*exp, delim);
    right_exp = mx_right_exp(*exp, delim);
    input = mx_first_word(right_exp);
    after_redirect = mx_rest_words(right_exp);
    *er = mx_extract_helper(input, &((*redirect)->output),
                            append, &((*redirect)->output_append));
    if (*er) {
        tmp = mx_strjoin_with_space(left_exp, after_redirect);
        mx_strdel(exp);
        *exp = tmp;
    }
    mx_delete_arlere(&after_redirect, &left_exp, &right_exp);
}

// ----    API Function
/**
 * Seeks << or < and extracts the following word
 * @param exp
 * @param redirect
 * @param er
 */
void mx_extract_input(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, "<<") != NULL) {         // есть ли <<

    }
    else if (strstr(*exp, "<") != NULL) {         // есть ли <
        _extract_input_helper("<", false, exp, redirect, er);
    }
    else {
        (*redirect)->input = NULL;
        (*redirect)->input_append = false; // it does not matter
        *er = true;
    }
}

/**
 * Seeks >> or > and extracts the following word
 * @param exp
 * @param redirect
 * @param er
 */
void mx_extract_output(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, ">>") != NULL) {         // есть ли <<
        _extract_output_helper(">>", true, exp, redirect, er);
    }
    else if (strstr(*exp, ">") != NULL) {         // есть ли <
        _extract_output_helper(">", false, exp, redirect, er);
    }
    else {
        (*redirect)->output = NULL;
        (*redirect)->output_append = false; // it does not matter
        *er = true;
    }
}

