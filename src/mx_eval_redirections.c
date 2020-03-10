//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"

void mx_reset_redirections(t_redirect *redir) {
    if (redir->prev_input_fd != 0) {
        dup2(redir->prev_input_fd, 0);
        if (mx_fd_is_valid(redir->prev_input_fd))
            close(redir->prev_input_fd);
    }
    if (redir->prev_output_fd != 1) {
        dup2(redir->prev_output_fd, 1);
        if (mx_fd_is_valid(redir->prev_output_fd))
            close(redir->prev_output_fd);
    }
    if (redir->prev_error_fd != 2) {
        dup2(redir->prev_error_fd, 2);
        if (mx_fd_is_valid(redir->prev_error_fd))
             close(redir->prev_error_fd);
    }
}

// apply_redirect
void apply_output_noappend(t_redirect *redir, bool *res) {
    if ((redir->output_fd = open(redir->output,
                                 O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
        perror(redir->output);
        exit (1);
    }
    if (redir->output_fd != 1) {
        redir->prev_output_fd = dup(1);
        dup2(redir->output_fd, 1);
        close(redir->output_fd);
        *res = true;
    }
}

void apply_output_append(t_redirect *redir, bool *res) {
    if ((redir->output_fd = open(redir->output,
                                 O_WRONLY|O_CREAT| O_APPEND, 0666)) < 0) {
        perror(redir->output);
        exit (1);
    }
    if (redir->output_fd != 1) {
        redir->prev_output_fd = dup(1);
        dup2(redir->output_fd, 1);
        close(redir->output_fd);
        *res = true;
    }
}

void apply_output(t_redirect *redir, bool *res) {
    if (!redir->output_append) {
        apply_output_noappend(redir, res);
    }
    if (redir->output_append) {
        apply_output_append(redir, res);
    }
}

bool mx_apply_redirect(t_redirect *redir) {
    bool res = false;
    if (redir == NULL)
        return res;
    if (redir->input != NULL) {
        if (!redir->input_append) {
            if ((redir->input_fd = open (redir->input, O_RDONLY)) < 0) {
                perror(redir->input);
                exit(1);
            }
            if (redir->input_fd != 0) {
                redir->prev_input_fd = dup(0);
                dup2(redir->input_fd, 0);
                close(redir->input_fd);
                res = true;
            }
        }
    }
    if (redir->output != NULL) {
        apply_output(redir, &res);
    }

    if (redir->error != NULL) {
        if ((redir->error_fd = open (redir->error,
                O_WRONLY|O_CREAT|O_TRUNC, 0666) ) < 0) {
            perror(redir->error);
            exit (1);
        }
        if (redir->error_fd != 2) {
            redir->prev_error_fd = dup(2);
            dup2 (redir->error_fd, 2);
            close (redir->error_fd);
            res = true;
        }
    }
    return res;
}

// extract
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

void mx_delete_arlere(char **after_redirect, char **left_exp, char
**right_exp) {
    mx_strdel(after_redirect);
    mx_strdel(left_exp);
    mx_strdel(right_exp);
}

void mx_extract_input_helper(char *delim, bool append, char **exp,
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

void mx_extract_output_helper(char *delim, bool append, char **exp, t_redirect **redirect,
        bool *er) {
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

void mx_extract_error_helper(char *delim, char **exp, t_redirect **redirect,
                              bool *er) {
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

void extract_input(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, "<<") != NULL) {         // есть ли <<

    }
    else if (strstr(*exp, "<") != NULL) {         // есть ли <
        mx_extract_input_helper("<", false, exp, redirect, er);
    }
    else {
        (*redirect)->input = NULL;
        (*redirect)->input_append = false; // it does not matter
        *er = true;
    }
}

void extract_output(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, ">>") != NULL) {         // есть ли <<
        mx_extract_output_helper(">>", true, exp, redirect, er);
    }
    else if (strstr(*exp, ">") != NULL) {         // есть ли <
        mx_extract_output_helper(">", false, exp, redirect, er);
    }
    else {
        (*redirect)->output = NULL;
        (*redirect)->output_append = false; // it does not matter
        *er = true;
    }
}

/*
 *     2>
 */
void extract_error(char **exp, t_redirect **redirect, bool *er) {
    if (strstr(*exp, "2>") != NULL) {         // есть ли <<
        mx_extract_error_helper("2>", exp, redirect, er);
    }
    else {
        (*redirect)->output = NULL;
        (*redirect)->output_append = false; // it does not matter
        *er = true;
    }
}

void mx_print_error_nearnewline() {
    mx_printstr("parse error near `\\n'\n");
}
/**
 *
 * @param exp это входящее и исходящее выражение без редиректов
 * @param redirections это структура, которую нужно про нью и заполнить
 */
bool mx_extract_redirections(t_exp *exp, t_redirect **redirections) {
    bool er;
    t_redirect *redirect = mx_new_redirect(exp, &er);
    *redirections = redirect;
    return er;
}

// API
void mx_delete_redirect(t_redirect **redirect) {
    if (*redirect == NULL)
        return ;
    mx_strdel(&((*redirect)->output));
    mx_strdel(&((*redirect)->input));
    mx_strdel(&((*redirect)->error));
    free(*redirect);
    *redirect = NULL;
}

// API
// возвращает структуру t_redirect
// меняет строку и удаляет редирекшины
static t_redirect *_malloc_new_redirect();
static void _error_handle(t_redirect **redirect);

t_redirect *mx_new_redirect(char **exp, bool *error) {
    bool er;
    t_redirect *redirect = _malloc_new_redirect();

    extract_error(exp, &redirect, &er);
    if (er == false)
        _error_handle(&redirect);
    else {
        extract_input(exp, &redirect, &er);
        if (er == false)
            _error_handle(&redirect);
        else {
            extract_output(exp, &redirect, &er);
            if (er == false)
                _error_handle(&redirect);
        }
    }
    *error = er;
    return redirect;
}

// for mx_new_redirect
static t_redirect *_malloc_new_redirect() {
    t_redirect *redirect = malloc(sizeof (t_redirect));
    redirect->error = NULL;
    redirect->input = NULL;
    redirect->output = NULL;
    redirect->input_fd = 0;
    redirect->prev_input_fd = 0;
    redirect->output_fd = 1;
    redirect->prev_output_fd = 1;
    redirect->error_fd = 2;
    redirect->prev_error_fd = 2;
    return redirect;
}
// for mx_new_redirect
static void _error_handle(t_redirect **redirect) {
    mx_print_error_nearnewline();
    mx_delete_redirect(redirect);
}

//
//#include <assert.h>
//// test extract_input
//int main(void) {
//    char *exp;
//    bool er;
//    t_redirect *redirect;
//
//    exp = strdup("ls -ls < input.txt >> output.txt 2> error.txt");
//    redirect = mx_new_redirect(&exp, &er);
//    printf("test 0\n");
//    printf("redirect='%s' output='%s' input='%s' error='%s'\n", exp,
//            redirect->output, redirect->input, redirect->error);
//    assert(strcmp(redirect->output, "output.txt") == 0);
//    assert(redirect->input_append == false);
//    assert(redirect->output_append == true);
//    assert(strcmp(redirect->input, "input.txt") == 0);
//    assert(strcmp(redirect->error, "error.txt") == 0);
//
//    free(exp);
//    mx_delete_redirect(&redirect);
//
//    exp = strdup("ls -ls < input.txt > output.txt 2> error.txt");
//    redirect = mx_new_redirect(&exp, &er);
//    printf("test 1\n");
//    printf("redirect='%s' output='%s' input='%s' error='%s'\n", exp,
//           redirect->output, redirect->input, redirect->error);
//    assert(strcmp(redirect->output, "output.txt") == 0);
//    assert(redirect->input_append == false);
//    assert(redirect->output_append == false);
//    assert(strcmp(redirect->input, "input.txt") == 0);
//    assert(strcmp(redirect->error, "error.txt") == 0);
//
//    free(exp);
//    mx_delete_redirect(&redirect);
//
//    exp = strdup("ls -ls  >output.txt 2> error.txt");
//    redirect = mx_new_redirect(&exp, &er);
//    printf("test 2\n");
//    printf("redirect='%s' output='%s' input='%s' error='%s'\n", exp,
//           redirect->output, redirect->input, redirect->error);
//    assert(strcmp(redirect->output, "output.txt") == 0);
//    assert(redirect->input_append == false);
//    assert(redirect->output_append == false);
//    assert(redirect->input == NULL);
//    assert(strcmp(redirect->error, "error.txt") == 0);
//
//    free(exp);
//    mx_delete_redirect(&redirect);
//
//    exp = strdup("ls -ls  >output.txt 2>");
//    redirect = mx_new_redirect(&exp, &er);
//    printf("test 3\n");
////    printf("redirect='%s' output='%s' input='%s' error='%s'\n", exp,
////           redirect->output, redirect->input, redirect->error);
//    assert(redirect == NULL);
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
