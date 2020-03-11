//
// Created by Oleg Berdyshev on 2/19/20.
//
#include "evaluator.h"

static char *_get_value(char *varname, t_global_environment *gv);

// ----    API Function

/**
 * Finds and substitutes all parameters
 * @param exp - mutable
 */
void mx_parameter_expansion(t_exp *exp, t_global_environment *gv) {
    int start = 0;
    int end = 0;
    char *name = NULL;
    char *value = NULL;
    bool find_result;

    find_result = mx_find_param(*exp, &start, &end, &name);
    while (find_result) {
        value = _get_value(name, gv);
        mx_insert(exp, start, end, value);
        mx_strdel(&value);
        mx_strdel(&name);
        find_result = mx_find_param(*exp, &start, &end, &name);
    }
}

void mx_insert(char **exp, int start, int end, char *word) {
    char *first = mx_strndup(*exp, start);
    char *last = mx_strndup(*exp + end + 1, mx_strlen(*exp) - end - 1);
    char *s1 = mx_strjoin(first, word);
    char *s2 = mx_strjoin(s1, last);

    mx_strdel(&s1);
    mx_strdel(&last);
    mx_strdel(&first);
    mx_strdel(exp);
    *exp = s2;
}

// ----- Static Functions

static char *_get_value(char *varname, t_global_environment *gv) {
    char *env_var_value = NULL;
    char *local_var_value = NULL;
    char *value = NULL;

    if (varname == NULL)
        return NULL;
    env_var_value = getenv(varname);
    if (env_var_value == NULL) {
        local_var_value = mx_env_get_value(varname, gv->vars);
        if (local_var_value != NULL)
            value = local_var_value;
    }
    else
        value = strdup(env_var_value);
    return value;
}

//////test mx_parameter_expansion
//#include <assert.h>
//int main(void) {
//    t_global_environment *gv = mx_new_global_env();
//    t_environment *env = mx_env_new();
//
//    mx_env_set_var("name", "Oleg", &env);
//    mx_env_set_var("Ilia", "Dovgopol", &env);
//    gv->vars = env;
//
//    char *arr[] = {"${HOME}", "${Ilia}", "$HOME", "$Ilia", "$HOME$name-",
//                   "\\$HOME$name", "$HOME\\$name", "$HOME\\\\$name"
//                   , NULL};
//    char *test[] = {"/Users/oberdyshev", "Dovgopol", "/Users/oberdyshev",
//                    "Dovgopol", "/Users/oberdyshevOleg-", "\\$HOMEOleg",
//                    "/Users/oberdyshev\\$name", "/Users/oberdyshev\\\\Oleg"};
//
//    for (int i = 0; arr[i]; i++) {
//        char *exp = strdup(arr[i]);
//        mx_parameter_expansion(&exp, gv);
//        printf("%d) '%s'\n", i + 1, exp);
//        assert( strcmp(exp, test[i]) == 0);
//        free(exp);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}


////// test mx_insert
//#include <assert.h>
//#include <string.h>
//int main(void) {
//    char *arr[] =  {"012$()345", "$()01", "0123$()", NULL};
//    int start[] =  { 3,         0,         4};
//    int end[] =    { 5,         2,         6};
//    char *test[] = {"012word345", "word01", "0123word", NULL};
//
//    for (int i = 0; arr[i]; i++) {
//        char *exp = mx_strdup(arr[i]);
//        mx_insert(&exp, start[i], end[i], "word");
//        printf("test %d) %s\n", i + 1, exp);
//        assert(strcmp(exp, test[i]) == 0);
//        free(exp);
//    }
//    system("leaks -q ush");
//    return 0;
//}
