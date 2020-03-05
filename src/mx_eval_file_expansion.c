//
// Created by Oleg Berdyshev on 3/5/20.
//

#include "evaluator.h"

char *mx_get_file_substitiution(char *name) {
    char *value = NULL;
    char *tmp = NULL;
    if (strcmp(name, "~-") == 0) {
        tmp = getenv("OLDPWD");
    }
    else if (strcmp(name, "~+") == 0) {
        tmp = getenv("PWD");
    }
    if (strcmp(name, "~") == 0) {
        tmp = getenv("HOME");
    }
    if (tmp != NULL)
        value = strdup(tmp);
    return value;
}

void mx_file_expansion(t_exp *exp) {
    int start = 0;
    int end = 0;
    char *name = NULL;
    char *value = NULL;
    bool find_result;

    find_result = mx_find_file_expansion(*exp, &start, &end, &name);
    while (find_result) {
        value = mx_get_file_substitiution(name);
        mx_insert(exp, start, end, value);
        free(value);
        free(name);
        find_result = mx_find_param(*exp, &start, &end, &name);
    }
}
//
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
//    char *arr[] = {"echo ~/hi",      "echo ~+",
//                   "echo '~'",    "echo '~-'",   "echo '~+'",
//                   "echo a~",    "echo a~-",   "echo a~+",
//                   NULL};
//    char *test[] = {"echo /Users/oberdyshev/hi",
//
//                    "echo /Users/oberdyshev/ush-ol/cmake-build-debug",
//                    "echo '~'",    "echo '~-'",   "echo '~+'",
//                    "echo a~",    "echo a~-",   "echo a~+",};
//
//    for (int i = 0; arr[i]; i++) {
//        char *exp = strdup(arr[i]);
//        mx_file_expansion(&exp);
//        printf("%d) '%s'\n", i + 1, exp);
//        assert( strcmp(exp, test[i]) == 0);
//        free(exp);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}

