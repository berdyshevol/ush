//
// Created by Oleg Berdyshev on 2/10/20.
//

#include "evaluator.h"

// ----    API Function
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

// do not use this function as api
void mx_apply_error(t_redirect *redir, bool *res) {
    if ((redir->error_fd = open (redir->error,
                                 O_WRONLY|O_CREAT|O_TRUNC, 0666) ) < 0) {
        perror(redir->error);
        exit (1);
    }
    if (redir->error_fd != 2) {
        redir->prev_error_fd = dup(2);
        dup2 (redir->error_fd, 2);
        close (redir->error_fd);
        *res = true;
    }
}
//// ----- Static Functions
//
//// apply_redirect
//void _apply_output_noappend(t_redirect *redir, bool *res) {
//    if ((redir->output_fd = open(redir->output,
//                                 O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
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
//void _apply_output_append(t_redirect *redir, bool *res) {
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
//        _apply_output_noappend(redir, res);
//    }
//    else {
//        _apply_output_append(redir, res);
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
