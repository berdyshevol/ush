//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----- Static Functions
static t_exp _command(t_exp exp) {
    t_exp first_word;
    char *s = strdup(exp);

    mx_trimleft(&s);
    first_word = mx_first_word(s);
    mx_strdel(&s);
    return first_word;
}

static t_exp _operands(t_exp exp) {
    char *s = strdup(exp);

    mx_trimleft(&s);
    t_exp operands = strdup(s); // операторы включают в себя название команды
    mx_strdel(&s);
    return operands;
}

static void _prepare_command_arguments_apply(t_exp exp,
                                             t_global_environment *gv,
                                             t_eval_result result) {
    t_eval_result apply_result = NULL;
    t_exp command = _command(exp);
    t_exp operands = _operands(exp);
    t_list_of_values *list_of_arguments = NULL;

    mx_list_of_values(&list_of_arguments, operands, gv);
    // apply
    apply_result = mx_apply(command, list_of_arguments, gv);
    result->status = apply_result->status;
    result->exit_no = apply_result->exit_no;

    mx_liststr_delete(&list_of_arguments);
    mx_strdel(&operands);
    mx_strdel(&command);
    mx_delete_evalresult(&apply_result);
}

static t_config *_init_cnf(t_global_environment *gv,
                           int *pipe_fd, bool *new_proc) {
    t_config *cnf;
    cnf = mx_config_new();
    cnf->pipe_fd = pipe_fd;
    cnf->new_proc = new_proc;
    gv->cnf = cnf;
    return cnf;
}

// ----    API Function
t_eval_result mx_simple_command(t_exp expression, t_global_environment *gv,
                                int *pipe_fd, bool *new_proc) {
    t_redirect *redirections = NULL;
    t_exp exp = strdup(expression);
    t_config *cnf = _init_cnf(gv, pipe_fd, new_proc);
    t_eval_result result = mx_new_evalresult();
    mx_parameter_expansion(&exp, gv);
    mx_command_substitution(&exp, result, gv);
    if (result->status == true) {
        mx_file_expansion(&exp);
        if (!mx_extract_redirections(&exp, &redirections))
            result->status = false;
        else {
            gv->cnf->redirections = redirections;
            _prepare_command_arguments_apply(exp, gv, result);
        }
    }
    mx_strdel(&exp);
    mx_delete_redirect(&redirections);
    mx_delete_config(&cnf);
    return result;
}


