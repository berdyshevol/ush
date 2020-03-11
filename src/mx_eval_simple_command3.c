//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

static void _remove_esc(t_exp exp, e_mode mode, int i, int *j, char *new_exp);
static void _remove_dquote(t_exp exp, e_mode *mode,
                           int i, int *j, char *new_exp);
static void _remove_quote(t_exp exp, e_mode *mode,
                          int i, int *j, char *new_exp);
static void _handle_oddnumberofqoutes(t_eval_result result);


// ----    API Function
//remove \ ' " from unquoted string
t_eval_result mx_eval_remove_escquotedquote(t_exp exp) {
    t_eval_result result = mx_new_evalresult();
    t_exp new_exp = mx_strnew(strlen(exp));
    int j = 0;
    e_mode mode = unquote;

    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '\\')
            _remove_esc(exp, mode, i, &j, new_exp);
        else if (exp[i] == '\"')
            _remove_dquote(exp, &mode, i, &j, new_exp);
        else if (exp[i] == '\'')
            _remove_quote(exp, &mode, i, &j, new_exp);
        else
            mx_copy(exp[i], new_exp, &j);
    }
    if (mode != unquote) {
        _handle_oddnumberofqoutes(result);
        mx_strdel(&new_exp);
    }
    else
        result->text = new_exp;
    return result;
}


// ----- Static Functions

static void _remove_esc(t_exp exp, e_mode mode, int i, int *j, char *new_exp) {
    if (mode == unquote) {
        if (mx_count_esc(exp, i) % 2 != 0)
            mx_copy('\\', new_exp, j);
    }
    else if (mode == dquote) {
        if (mx_count_esc(exp, i) % 2 == 0
            && (exp[i + 1] != '\"' && exp[i + 1] != '\'') )
            mx_copy('\\', new_exp, j);
    }
    else
        mx_copy('\\', new_exp, j);
}

static void _remove_dquote(t_exp exp, e_mode *mode,
                           int i, int *j, char *new_exp) {
    if (*mode == unquote) {
        if (mx_count_esc(exp, i) % 2 != 0)
            mx_copy('\"', new_exp, j);
        else
            *mode = dquote;
    }
    else if (*mode == dquote) {
        if (mx_count_esc(exp, i) % 2 != 0)
            mx_copy('\"', new_exp, j);
        else
            *mode = unquote;
    }
    else
        mx_copy('\"', new_exp, j);
}

static void _remove_quote(t_exp exp, e_mode *mode,
                          int i, int *j, char *new_exp) {
    if (*mode == unquote) {
        if (mx_count_esc(exp, i) % 2 != 0)
            mx_copy('\'', new_exp, j);
        else
            *mode = quote;
    }
    else if (*mode == dquote) {
        mx_copy('\\', new_exp, j);
    }
    else if (*mode == quote)
        *mode = unquote;
}

static void _handle_oddnumberofqoutes(t_eval_result result) {
    result->status = false;
    result->text = NULL;
    mx_print_oddnumberofquotes();
}

//////test eval_remove_escquotedquote
//#include <assert.h>
//int main(void) {
//    t_exp exp;
//    char *arr[] =  {
//
//            "oo\\\\\"oo\\\"oo\"", "oo\'oo\\\"oo\'oo",
//            "-\'-\\-\'", "o\'o\\\\o\'", "o\'o\\\\\\o\'",
//            "-\"-\\-\"", "o\"o\\\\o\"", "o\"o\\\\\\o\"",
//            "oo\\", "oo\\\\", "oo\\\\\\", "oo\\\\\\\\",
//            "'oo'", "\\\'oo\\\'",
//
//            NULL};
//    char *test[] = {
//
//            "oo\\oo\"oo", "oooo\\\"oooo",
//            "--\\-", "oo\\\\o", "oo\\\\\\o",
//            "--\\-", "oo\\o", "oo\\\\o",
//            "oo", "oo\\", "oo\\", "oo\\\\",
//            "oo", "'oo'",
//
//                   };
//    for (int i = 0; arr[i]; i++) {
//        exp = strdup(arr[i]);
//        t_eval_result result = mx_eval_remove_escquotedquote(exp);
//        printf("test %d) <<%s>>\n", i+1, result->text);
//        assert(strcmp(result->text, test[i]) == 0);
//        free(exp);
//        mx_delete_evalresult(&result);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
