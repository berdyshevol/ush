//
// Created by Oleg Berdyshev on 3/5/20.
//

#include "parser.h"

static bool _is_tilda_minus(char *exp, int i, t_args *args) {
    // check if this is ~-
    if (i != mx_strlen(exp) && exp[i + 1] == '-') {
        args->start = i;
        args->end = i + 1;
        args->name = strdup("~-");
        return true;
    }
    else
        return false;
}

static bool _is_tilda_plus(char *exp, int i, t_args *args) {
    if (i != mx_strlen(exp) && exp[i + 1] == '+') {
        args->start = i;
        args->end = i + 1;
        args->name = strdup("~+");
        return true;
    }
    else
        return false;
}

static void _is_tilda(int i, t_args *args) {
    args->start = i;
    args->end = i;
    args->name = strdup("~");
}

static bool _is_file_expansion(char *exp, e_mode mode, int i, t_args *args) {
    if (exp[i] == '~' && mode == unquote) {
        // check if this is the beginning of the word
        if (i == 0 || mx_is_whitespace(exp[i - 1])) {
            if (_is_tilda_minus(exp, i, args)) {
                return true;
            }
            else if (_is_tilda_plus(exp, i, args)){
                return true;
            }
            else {
                _is_tilda(i, args);
                return true;
            }
        }
    }
    return false;
}

bool mx_find_file_expansion(char *exp, int *start, int *end, char **name) {
    e_mode mode = unquote;
    t_args *args = mx_args_new();
    bool result = false;

    for (unsigned long i = 0; i < strlen(exp); i++) {
        mx_change_mode(&mode, exp, i);
        if (_is_file_expansion(exp, mode, i, args)) {
            result = true;
            break;
        }
    }
    if (result)
        mx_set(args, start, end, name);
    else
        mx_reset(start, end, name);
    mx_args_delete(&args);
    return result;
}

//////test mx_find_param
//#include <assert.h>
//int main(void) {
//    char *exp[] =      {"echo ~",   "echo ~+",  "echo ~-",
//                        "echo '~'", "echo' ~+'", "echo' ~-'",
//                        "echo 1~",   "echo 1~+",  "echo 1~-", NULL};
//    int test_start[] = {5,           5,         5,
//                        0,           0,         0,
//                        0,           0,         0,};
//    int test_end[] =   {5,          6,          6,
//                        0,          0,          0,
//                        0,           0,         0,};
//    char *test_name[]={ "~",     "~+",           "~-",
//                        NULL,       NULL,       NULL,
//                        NULL,       NULL,       NULL};
//    int start;
//    int end;
//    char *name;
//
//    for (int i = 0; exp[i]; i++) {
//        mx_find_file_expansion(exp[i], &start, &end, &name);
//        printf("%d) %s\t%d\t%d\t%s\n", i + 1, exp[i], start, end, name);
//        assert(start == test_start[i]);
//        assert(end == test_end[i]);
//        if (name != NULL)
//            assert(strcmp(name, test_name[i]) == 0);
//        else
//            assert(name == test_name[i]);
//        free(name);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
