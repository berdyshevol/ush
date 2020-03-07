//
// Created by Олег on 3/6/20.
//

#include "parser.h"

//void mx_print_oddnumberofparentheses(void){
//    mx_printerr("Odd number of parentheses\n");
//}

bool mx_find_command_substitution(char *exp, int *start, int *end, char **name) {
    *start = 0;
    *name = NULL;
    e_mode mode = unquote;
    char *find_begin = NULL;

    for (unsigned long i = 0; i < strlen(exp); i++) {
        //char *find_begin = strstr(&exp[i], "$");
        mx_change_mode(&mode, exp, i);
        if (exp[i] == '$' && mode != quote) {
            find_begin = &exp[i];
            //if (find_begin) {
            if (mx_count_esc(exp, find_begin - exp) % 2 != 0)
                continue;
            if (find_begin[1] == '(') {
                *start = find_begin - exp;
                char *find_end = mx_strstr_esc_rev(find_begin, ")");
                if (find_end == NULL)
                    *end = strlen(exp) - 1;
                else {
                    *end = find_end - exp;
                    *name = strndup(exp + *start + 2, *end - *start - 2);
                    return true;
                }
            }
        }
        else if (exp[i] == '`' && mode != quote) {
            find_begin = &exp[i];
            if (mx_count_esc(exp, find_begin - exp) % 2 != 0)
                continue;
            *start = find_begin - exp;
            char *find_end = mx_strstr_esc_rev(find_begin + 1, "`");
            // if find_end == NULL no error handle
            *end = find_end - exp;
            *name = strndup(exp + *start + 1, *end - *start - 1);
            return true;
        }
    }
    *end = 0;
    return false;
}

////test mx_find_param
//#include <assert.h>
//int main(void) {
//    char *exp[] =      {
//                        "$(name $(name)) ",        "name\n $(name)",
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
//                        14,        12,
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

