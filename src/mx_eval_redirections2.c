//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"

static void _extract_error_helper(char *delim, char **exp,
                                  t_redirect **redirect, bool *er);

// ----    API Function
/**
 * Seeks 2> and extracts the following word
 * @param exp
 * @param redirect
 * @param er
 */
void mx_extract_error(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, "2>") != NULL) {         // есть ли <<
        _extract_error_helper("2>", exp, redirect, er);
    }
    else {
        (*redirect)->output = NULL;
        (*redirect)->output_append = false; // it does not matter
        *er = true;
    }
}

bool mx_extract_helper(char *str_value,char **str_field,
                       bool bool_value, bool *bool_field) {
    bool res;
    if (str_value != NULL) {
        res = true;
        *str_field = str_value;
        if (bool_field != NULL)
            *bool_field = bool_value;
    }
    else {
        res = false;
        *str_field = NULL;
    }
    return res;
}

void mx_delete_arlere(char **after_redirect,
                      char **left_exp, char **right_exp) {
    mx_strdel(after_redirect);
    mx_strdel(left_exp);
    mx_strdel(right_exp);
}

// ----- Static Functions
static void _extract_error_helper(char *delim, char **exp,
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
    *er = mx_extract_helper(input, &((*redirect)->error), NULL, er);
    if (*er) {
        tmp = mx_strjoin_with_space(left_exp, after_redirect);
        mx_strdel(exp);
        *exp = tmp;
    }
    mx_delete_arlere(&after_redirect, &left_exp, &right_exp);
}
//
//
//void apply_output_append(t_redirect *redir, bool *res) {
//    if ((redir->output_fd = open(redir->output,
//                                 O_WRONLY|O_CREAT| O_APPEND, 0666)) < 0) {
//        perror(redir->output);
//        exit (1);
//    }
//    if (redir->output_fd != 1) {
//        redir->prev_output_fd = dup(1);
//        dup2(redir->output_fd, 1);
//        close(redir->output_fd);
//        *res = true;
//    }
//}
//
//void _apply_output(t_redirect *redir, bool *res) {
//    if (!redir->output_append) {
//        apply_output_noappend(redir, res);
//    }
//    else {
//        apply_output_append(redir, res);
//    }
//}
//
//void _apply_input(t_redirect *redir, bool *res) {
//    if (!redir->input_append) {
//        if ((redir->input_fd = open (redir->input, O_RDONLY)) < 0) {
//            perror(redir->input);
//            exit(1);
//        }
//        if (redir->input_fd != 0) {
//            redir->prev_input_fd = dup(0);
//            dup2(redir->input_fd, 0);
//            close(redir->input_fd);
//            *res = true;
//        }
//    }
//}
//
//void mx_apply_error(t_redirect *redir, bool *res) {
//    if ((redir->error_fd = open (redir->error,
//                                 O_WRONLY|O_CREAT|O_TRUNC, 0666) ) < 0) {
//        perror(redir->error);
//        exit (1);
//    }
//    if (redir->error_fd != 2) {
//        redir->prev_error_fd = dup(2);
//        dup2 (redir->error_fd, 2);
//        close (redir->error_fd);
//        *res = true;
//    }
//}
//
//bool mx_apply_redirect(t_redirect *redir) {
//    bool res = false;
//    if (redir == NULL)
//        return res;
//    if (redir->input != NULL) {
//        _apply_input(redir, &res);
//    }
//    if (redir->output != NULL) {
//        _apply_output(redir, &res);
//    }
//
//    if (redir->error != NULL) {
//        mx_apply_error(redir, &res);
//    }
//    return res;
//}
//
//
//
//
//
//void mx_extract_input_helper(char *delim, bool append, char **exp,
//                            t_redirect **redirect, bool *er) {
//    char *right_exp;
//    char *left_exp;
//    char *after_redirect;
//    char *input;
//    char *tmp;
//
//    left_exp = mx_left_exp(*exp, delim);
//    right_exp = mx_right_exp(*exp, delim);
//    input = mx_first_word(right_exp);
//    after_redirect = mx_rest_words(right_exp);
//    *er = mx_extract_helper(input, &((*redirect)->input), append, &((*redirect)
//    ->input_append));
//    if (*er) {
//        tmp = mx_strjoin_with_space(left_exp, after_redirect);
//        mx_strdel(exp);
//        *exp = tmp;
//    }
//    mx_delete_arlere(&after_redirect, &left_exp, &right_exp);
//}
//
//void mx_extract_output_helper(char *delim, bool append, char **exp, t_redirect **redirect,
//        bool *er) {
//    char *right_exp;
//    char *left_exp;
//    char *after_redirect;
//    char *input;
//    char *tmp;
//
//    left_exp = mx_left_exp(*exp, delim);
//    right_exp = mx_right_exp(*exp, delim);
//    input = mx_first_word(right_exp);
//    after_redirect = mx_rest_words(right_exp);
//    *er = mx_extract_helper(input, &((*redirect)->output),
//                           append, &((*redirect)->output_append));
//    if (*er) {
//        tmp = mx_strjoin_with_space(left_exp, after_redirect);
//        mx_strdel(exp);
//        *exp = tmp;
//    }
//    mx_delete_arlere(&after_redirect, &left_exp, &right_exp);
//}
//
//
//
////    <   <<
//void mx_extract_input(char **exp, t_redirect **redirect, bool *er) {
//    if (strstr(*exp, "<<") != NULL) {         // есть ли <<
//
//    }
//    else if (strstr(*exp, "<") != NULL) {         // есть ли <
//        mx_extract_input_helper("<", false, exp, redirect, er);
//    }
//    else {
//        (*redirect)->input = NULL;
//        (*redirect)->input_append = false; // it does not matter
//        *er = true;
//    }
//}
//
////   >   >>
//void mx_extract_output(char **exp, t_redirect **redirect, bool *er) {
//    if (strstr(*exp, ">>") != NULL) {         // есть ли <<
//        mx_extract_output_helper(">>", true, exp, redirect, er);
//    }
//    else if (strstr(*exp, ">") != NULL) {         // есть ли <
//        mx_extract_output_helper(">", false, exp, redirect, er);
//    }
//    else {
//        (*redirect)->output = NULL;
//        (*redirect)->output_append = false; // it does not matter
//        *er = true;
//    }
//}
