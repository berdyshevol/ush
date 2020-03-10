//
// Created by Олег on 3/6/20.
//

#include "parser.h"

// ----    API Functions
t_args *mx_args_new(void) {
    t_args *args = malloc(sizeof (t_args));
    args->name = NULL;
    args->start = 0;
    args->end = 0;
    return args;
}

void mx_args_delete(t_args **args) {
    free(*args);
    *args = NULL;
}

void mx_reset(int *a, int *b, char **s) {
    *a = 0;
    *b = 0;
    *s = NULL;
}

void mx_set(t_args *args, int *start, int *end, char **name) {
    *start = args->start;
    *end = args->end;
    *name = args->name;
}

// // Находит последовательности подстановок комманд.
//// Но вложенные подстановки только $( ` ` )  `  $(  )  `
//// Но не парсит $( $( ) )
//bool mx_find_command_substitution(char *exp, int *start, int *end, char **name) {
//    e_mode mode = unquote;
//    t_args *args = mx_args_new();
//    for (unsigned long i = 0; i < strlen(exp); i++) {
//        mx_change_mode(&mode, exp, i);
//        switch (cmd_subs(exp, i, mode, args)) {
//            case continue_loop:
//                continue;
//            case return_true:
//                mx_set(args, start, end, name);
//                mx_args_delete(&args);
//                return true;
//            case break_loop:
//                break;
//        }
//    }
//    mx_args_delete(&args);
//    mx_reset(start, end, name);
//    return false;
//}

////test mx_find_param
//#include <assert.h>
//int main(void) {
//    char *exp[] =      {
//                        "$(name `name`) ",        "name\n ` $(name) `",
//                        "`name`",  "\"`name`\"",          "'`name`'",     "'`na'`name`",
//                        "$(name)", "\"$(name)\"'$(name",  "'$(name)'",
//                        "\\$( $(name)", "$(name\\))'$(name",  "'$(name)'",
//
//                        NULL};
//    int test_start[] = {
//                        0,        6,
//                        0,        1,                     0,   5,
//                        0,        1,                     0,
//                        4,        0,                     0,
//
//                        };
//    int test_end[] =   {
//                        13,        16,
//                        5,        6,                    0,     10,
//                        6,        7,                    0,
//                        10,       8,                    0,
//
//                        };
//    int start;
//    int end;
//    char *name;
//
//    for (int i = 0; exp[i]; i++) {
//        mx_find_command_substitution(exp[i], &start, &end, &name);
//        printf("%d) %s\t%d\t%d\t<<%s>>\n", i + 1, exp[i], start, end, name);
//        assert(start == test_start[i]);
//        assert(end == test_end[i]);
//        free(name);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
//
