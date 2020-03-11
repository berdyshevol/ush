//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----- Static Functions
static t_eval_result _left_pipe(t_exp exps, t_global_environment *gv,
                                int *fd, bool *new_proc) {
    char *delim = "|";
    char *first_exp = mx_first_exp(exps, delim);

    t_eval_result eval_fe = mx_eval(first_exp, gv, fd, new_proc);

    mx_strdel(&first_exp);
    return eval_fe;
}

static t_eval_result _right_pipe_sequence(t_exp exps, t_global_environment *gv,
                                          int *fd) {
    char *delim = "|";
    char *rest_exps = mx_rest_exps(exps, delim);
    t_eval_result result = mx_eval_seq_pipeline(rest_exps, gv, fd);
    mx_strdel(&rest_exps);
    return result;
}

// ----    API Function
t_eval_result mx_eval_seq_pipeline(t_exp exps,
                                   t_global_environment *gv, int *pipe_fd) {
    t_eval_result result = NULL;
    char *delim = "|";
    bool *new_proc = malloc(sizeof(bool));

    if (mx_is_last_exp(exps, delim)) {
        *new_proc = false; // for last right pipe
        result = _left_pipe(exps, gv, pipe_fd, new_proc);
    }
    else {
        int fd[2];
        pipe(fd);
        *new_proc = true; // for last pipe which is not last pipe
        t_eval_result eval_fe = _left_pipe(exps, gv, fd, new_proc);
        result = _right_pipe_sequence(exps, gv, fd);
        mx_delete_evalresult(&eval_fe);
    }
    free(new_proc);
    return result;
}


