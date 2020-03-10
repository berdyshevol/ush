#include "parser.h"

// ----    API Function

void mx_split_two_str(char *exp, char *operator,
                      char **left_string, char **right_string) {
    char *left_substr = NULL;
    char *right_substr = NULL;
    char *p = NULL;

    p = mx_smart_find(exp, operator);
    if (p != NULL) {
        int n = p - exp;
        left_substr = mx_strndup(exp, n);
        n = (int) ((exp + (int)strlen(exp) - 1) - p);
        right_substr = mx_strndup(p + strlen(operator), n);
    }
    else {
        left_substr = strdup(exp);
        right_substr = strdup("");
    }
    mx_trimleft(&left_substr);
    *left_string = left_substr;
    mx_trimleft(&right_substr);
    *right_string = right_substr;
//    mx_trimleft(&left_substr); //    *left_string = mx_trim(left_substr);
//    *left_string = strdup(left_substr);
//    mx_trimleft(&right_substr); //    *right_string = mx_trim(right_substr);
//    *right_string = strdup(right_substr);
//    mx_strdel(&left_substr);
//    mx_strdel(&right_substr);
}

// #include <assert.h>
// #include <stdio.h>
//
// int main(void) {
//     printf("split two str\n\n");
//     char *s = "H'el'lo;World";
//     char *op = ";";
//     char *ls = NULL;
//     char *rs = NULL;
//
//     mx_split_two_str(s, op, &ls, &rs);
//     printf("1) '%s' => '%s' and '%s'\n", s, ls, rs);
//     assert(strcmp(ls, "H'el'lo") == 0);
//     assert(strcmp(rs, "World") == 0);
//
//     char *s0 = "Hello; ";
//     char *ls0 = NULL;
//     char *rs0 = NULL;
//
//     mx_split_two_str(s0, op, &ls0, &rs0);
//     printf("2) '%s' => '%s' and '%s'\n", s0, ls0, rs0);
//     assert(strcmp(ls0, "Hello") == 0);
//     assert(strcmp(rs0, "") == 0);
//
//     char *s1 = "Hel\\ 'lo' || World ";
//     char *op1 = "||";
//     char *ls1 = NULL;
//     char *rs1 = NULL;
//
//     mx_split_two_str(s1, op1, &ls1, &rs1);
//     printf("3) '%s' => '%s' and '%s'\n", s1, ls1, rs1);
//     assert(strcmp(ls1, "Hel\\ 'lo' ") == 0);
//     assert(strcmp(rs1, "World ") == 0);
//
//     char *s2 = "Hello || ";
//     char *ls2 = NULL;
//     char *rs2 = NULL;
//
//     mx_split_two_str(s2, op1, &ls2, &rs2);
//     printf("4) '%s' => '%s' and '%s'\n", s2, ls2, rs2);
//     assert(strcmp(ls2, "Hello ") == 0);
//     assert(strcmp(rs2, "") == 0);
//
//     char *s21 = "Hello\\ W`orld || Ol`eg";
//     char *ls21 = NULL;
//     char *rs21 = NULL;
//
//     mx_split_two_str(s21, op1, &ls21, &rs21);
//     printf("5) '%s' => '%s' and '%s'\n", s21, ls21, rs21);
//     assert(strcmp(ls21, "Hello\\ W`orld || Ol`eg") == 0);
//     assert(strcmp(rs21, "") == 0);
//
//    printf("\nSUCCESS\n-----\n");
//
//    system("leaks -q ush");
//     return 0;
// }

