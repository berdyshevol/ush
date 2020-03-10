//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"
static t_redirect *_malloc_new_redirect();
static void _error_handle(t_redirect **redirect);

// ----    API Function

/**
 *
 * @param exp mutable parameter
 * @param redirections - is a structure with file_in, file_out, file_error
 */
bool mx_extract_redirections(t_exp *exp, t_redirect **redirections) {
    bool er;
    t_redirect *redirect = mx_new_redirect(exp, &er);
    *redirections = redirect;
    return er;
}

void mx_delete_redirect(t_redirect **redirect) {
    if (*redirect == NULL)
        return ;
    mx_strdel(&((*redirect)->output));
    mx_strdel(&((*redirect)->input));
    mx_strdel(&((*redirect)->error));
    free(*redirect);
    *redirect = NULL;
}

t_redirect *mx_new_redirect(char **exp, bool *error) {
    bool er;
    t_redirect *redirect = _malloc_new_redirect();

    mx_extract_error(exp, &redirect, &er);
    if (er == false)
        _error_handle(&redirect);
    else {
        mx_extract_input(exp, &redirect, &er);
        if (er == false)
            _error_handle(&redirect);
        else {
            mx_extract_output(exp, &redirect, &er);
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

