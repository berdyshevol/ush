#include "ush.h"

static t_pair_cmd_name builtin[] = {
        {"export", mx_builtin_export},
        {"unset", mx_builtin_unset},
        {"exit", mx_builtin_exit},
        {"env", mx_builtin_env},
        {"cd", mx_builtin_cd},
        {"pwd", mx_builtin_pwd},
        {"which", mx_builtin_which},
        {"echo", mx_builtin_echo},
        {"fg", mx_builtin_fg},
        {"jobs", mx_jobs},
        {"yes", mx_yes},
        {"true", mx_true},
        {"false", mx_false},
        {NULL, NULL}
};

static int _find_builtin(char *cmd) {
    int i = 0;
    while (builtin[i].name) {
        if (strcmp(cmd, builtin[i].name) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

void mx_execute_builtin_innewproc(int id, t_eval_result result, t_global_environment *gv) {
    int pid;
    int status;
    switch (pid = fork()) {
        case -1:
            perror ("fork");
            break;
        case 0:
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[1] != 1) {
                    dup2(gv->cnf->pipe_fd[1], 1);
                    close(gv->cnf->pipe_fd[1]);
                }
                close(gv->cnf->pipe_fd[0]);
            }
            mx_run_builtin(id, result, gv);
            exit(result->status ? 0 : 1);
            break;
        default:
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[0] != 0) {
                    dup2(gv->cnf->pipe_fd[0], 0);
                    close(gv->cnf->pipe_fd[0]);
                }
                close(gv->cnf->pipe_fd[1]);
            }
            waitpid (pid, &status, 0);
            mx_set_input_mode();
            //int i = mx_wexitstatud(status);
            char *itoa =  mx_itoa(mx_wexitstatud(status));
            mx_env_set_var("?", itoa, &(gv->vars));
            result->status = mx_wexitstatud(status) == 0 ? true : false;
            mx_strdel(&itoa);
            break;
    }
}

void mx_run_builtin(int id, t_eval_result result, t_global_environment *gv) {
    int exit_status;
//    t_redirect *redir = gv->cnf->redirections;

    if (mx_apply_redirect(gv->cnf->redirections)) {
        exit_status = builtin[id].cmd(gv);
        mx_reset_redirections(gv->cnf->redirections);
    }
    else
        exit_status = builtin[id].cmd(gv);

    char *itoa = mx_itoa(exit_status);
    mx_env_set_var("?", itoa, &(gv->vars));
    result->status = (exit_status == EXIT_SUCCESS);
    mx_strdel(&itoa);
    // -- old
//    mx_apply_redirect(redir);
//    exit_status = builtin[id].cmd(gv);
//    mx_reset_redirections(redir);
//    mx_env_set_var("?", mx_itoa(exit_status), &(gv->vars));
//    result->status = (exit_status == EXIT_SUCCESS);
}

bool try_builtin(char *cmd, t_eval_result result, t_global_environment *gv) {
    int id = _find_builtin(cmd);

    if (id >= 0) {
        if (gv->cnf->new_proc != NULL && *(gv->cnf->new_proc) == true) {
            mx_execute_builtin_innewproc(id, result, gv);
        }
        else {
            if (mx_has_pipe(gv->cnf->pipe_fd)) {
                if (gv->cnf->pipe_fd[0] != 0) {
                    dup2(gv->cnf->pipe_fd[0], 0);
                    close(gv->cnf->pipe_fd[0]);
                }
                close(gv->cnf->pipe_fd[1]);
            }
            mx_run_builtin(id, result, gv);
        }
        return true;
    }
    else  // no builtin found
        return false;
}

t_eval_result
mx_execute(char *command, t_global_environment *gv) {
    t_eval_result result = mx_new_evalresult();

    if (try_builtin(command, result, gv)) {
    }
    else if (mx_try_bin(command, result, gv)) {
    }
    return result;
}
// //
// int main(void) {
//     t_global_environment *gv = mx_new_global_env();
// //    char *s = "echo";
// //    char *s = "echo l o ";
// //    char *s = "echo \"hi oleg\"";
//     //char *s = "echo \'hi oleg\'";
// //    char *s = "oleg=hi";
// //    char *s = strdup("oleg=\"hi\" hi; echo oleg $oleg $HOME; ls -la");
// //    char *s =  "oleg=\"hi\" echoo \"$oleg ++\"; echo oleg $oleg";
// //    char *s =  "oleg=\"hi\" echoo \"$oleg ++\"; echo oleg ${PWD} ${oleg}";
//  //   char *s =  "echo pwd= ${PWD} oleg ${oleg}";
// // char *s;
// // s="name=Oleg n=Ilia !; echo \\\"hi\\\" $name \\\"-${n}-\\\" && echo ok $HOME "
// //   "|| "
// //   "echo error && echo more error";
// //    char *s = strdup("oleg=\"hi\" hi; echo oleg $oleg $HOME; ls");
// //    char *s = strdup("ls -l ./ dfgds  && echo ok || echo "
// //                     "bad ; ");
//
// //    char *s = strdup("ls /bin > test; cat test");
// //    char *s = strdup("name=Oleg; echo hi $name >> test; cat < test");
// //    char *s = strdup("name=Oleg; echo Hi $name > test; cat test | wc -w");
//
//     char *s = strdup("name=Oleg; echo $name");
//     t_eval_result result = mx_eval(s, gv, NULL, NULL);
//
//     mx_delete_evalresult(&result);
//     mx_delete_global_env(&gv); // здесь есть лики
//
//     system("leaks -q ush");
//     return 0;
// }
