////
//// Created by Oleg Berdyshev on 2/6/20.
////
//
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
        {"alias", mx_alias},
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

bool try_builtin(char *cmd, t_eval_result result, t_global_environment *gv,
                 t_redirect *redir) {
    int id = _find_builtin(cmd);
    int pid;
    int exit_status;

    if (id >= 0) {
//        if (gv->cnf->for_process) {
//            switch (pid = fork ()) {
//                case -1:
//                    perror("fork");
//                    break;
//                case 0: // child TODO: где-то здесь нужно сделать редир 1
//                    result->status = (builtin[id].cmd(gv) == EXIT_SUCCESS);
//                    break;
//                default:
//                    waitpid(pid, NULL, 0);
//                    break;
//            }
//        }
//        else
        mx_apply_redirect(redir);
        exit_status = builtin[id].cmd(gv);
        mx_reset_redirections(redir);
        mx_env_set_var("?", mx_itoa(exit_status), &(gv->vars));
        result->status = (exit_status == EXIT_SUCCESS);
        return true;
    }
    else  // no builtin found
        return false;
}

t_eval_result
mx_execute(char *command, t_global_environment *gv) {
    t_eval_result result = mx_new_evalresult();
    printf("in execute cmd=%s\n", command);
    if (try_builtin(command, result, gv, gv->cnf->redirections)) {

    }
    else if (mx_try_bin(command, result, gv, gv->cnf->redirections)) {
        // TODO: здесь нужно попробовать запусть бинарник
        // TODO: если результат ошибка то надо обработать ошибку
    }
    return result;
}
//
//int main(void) {
//    t_global_environment *gv = mx_new_global_env();
////    char *s = "echo";
////    char *s = "echo l o ";
////    char *s = "echo \"hi oleg\"";
//    //char *s = "echo \'hi oleg\'";
////    char *s = "oleg=hi";
////    char *s = strdup("oleg=\"hi\" hi; echo oleg $oleg $HOME; ls -la");
////    char *s =  "oleg=\"hi\" echoo \"$oleg ++\"; echo oleg $oleg";
////    char *s =  "oleg=\"hi\" echoo \"$oleg ++\"; echo oleg ${PWD} ${oleg}";
// //   char *s =  "echo pwd= ${PWD} oleg ${oleg}";
//// char *s;
//// s="name=Oleg n=Ilia !; echo \\\"hi\\\" $name \\\"-${n}-\\\" && echo ok $HOME "
////   "|| "
////   "echo error && echo more error";
////    char *s = strdup("oleg=\"hi\" hi; echo oleg $oleg $HOME; ls");
////    char *s = strdup("ls -l ./ dfgds  && echo ok || echo "
////                     "bad ; ");
//
//    char *s = strdup("name=Oleg; echo $name; echo $name");
//    t_eval_result result = mx_eval(s, gv);
//
//    mx_delete_evalresult(&result);
//    mx_delete_global_env(&gv); // здесь есть лики
//
////    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
