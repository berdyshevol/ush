//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"

static void _apply_input(t_redirect *redir, bool *res);
static void _apply_output(t_redirect *redir, bool *res);
static void apply_output_append(t_redirect *redir, bool *res);
static void apply_output_noappend(t_redirect *redir, bool *res);

// ----    API Function
bool mx_apply_redirect(t_redirect *redir) {
    bool res = false;
    if (redir == NULL)
        return res;
    if (redir->input != NULL) {
        _apply_input(redir, &res);
    }
    if (redir->output != NULL) {
        _apply_output(redir, &res);
    }

    if (redir->error != NULL) {
        mx_apply_error(redir, &res);
    }
    return res;
}

// ----- Static Functions
static void _apply_input(t_redirect *redir, bool *res) {
    if (!redir->input_append) {
        if ((redir->input_fd = open (redir->input, O_RDONLY)) < 0) {
            perror(redir->input);
            exit(1);
        }
        if (redir->input_fd != 0) {
            redir->prev_input_fd = dup(0);
            dup2(redir->input_fd, 0);
            close(redir->input_fd);
            *res = true;
        }
    }
}

static void _apply_output(t_redirect *redir, bool *res) {
    if (!redir->output_append) {
        apply_output_noappend(redir, res);
    }
    else {
        apply_output_append(redir, res);
    }
}

static void apply_output_append(t_redirect *redir, bool *res) {
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

// apply_redirect
static void apply_output_noappend(t_redirect *redir, bool *res) {
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

