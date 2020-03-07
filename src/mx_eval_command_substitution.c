//
// Created by Олег on 3/6/20.
//

#include "ush.h"
#include "evaluator.h"

char *mx_readpipe(int fd) {
    int size = 1024;
    char buf[size];
    int res;
    if ((res = read(fd, buf, size)) > 0) {
        return strndup(buf, res);
    }
    else return NULL;
}

char *mx_get_command_substitution(char *exp, t_eval_result result, t_global_environment *gv) {
    char *res = NULL;
//    t_eval_result new_res = NULL;
    int fd[2];
    int pid = -1;

    pipe(fd);
    switch ((pid = fork())) {
        case -1:
            result->status = false;
            break;
        case 0:
            if (fd[1] != 1) {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            close(fd[0]);
            int exit_no;
            t_eval_result child_res = mx_eval(exp, gv, NULL, NULL);
            exit_no = child_res->exit_no;
            mx_delete_evalresult(&child_res);
            exit(exit_no);
            break;
        default:
            mx_smart_wait(pid, result, gv);
            res = mx_readpipe(fd[0]);
            mx_smart_close_fd(&fd[0], 0);
            mx_smart_close_fd(&fd[1], 1);
            break;
    }

    return res;
}

void mx_command_substitution(t_exp *exp, t_eval_result result, t_global_environment *gv) {
    int start = 0;
    int end = 0;
    char *name = NULL;
    char *value = NULL;
    bool find_result;

    find_result = mx_find_command_substitution(*exp, &start, &end, &name);
    while (find_result) {
        value = mx_get_command_substitution(name, result, gv);
        mx_insert(exp, start, end, value);
        mx_strdel(&value);
        mx_strdel(&name);
        find_result = mx_find_param(*exp, &start, &end, &name);
    }
}

//////test mx_parameter_expansion
//#include <assert.h>
//int main(void) {
////    t_global_environment *gv = mx_new_global_env();
////    t_environment *env = mx_env_new();
////
////    mx_env_set_var("name", "Oleg", &env);
////    mx_env_set_var("Ilia", "Dovgopol", &env);
////    gv->vars = env;
//
//    char *arr[] = {"$(echo hi)",
//                   NULL};
//    char *test[] = {"hi",
//
//                    };
//
//    for (int i = 0; arr[i]; i++) {
//        char *exp = strdup(arr[i]);
//        mx_command_substitution(&exp, NULL, NULL);
//        printf("%d) '%s'\n", i + 1, exp);
//        assert( strcmp(exp, test[i]) == 0);
//        free(exp);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
//
