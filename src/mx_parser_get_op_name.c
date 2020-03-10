//
// Created by Oleg Berdyshev on 1/30/20.

#include "parser.h"

char *mx_get_op_name(char *exp) {
    return mx_get_name_by_id(mx_get_binary_opid(exp));
}
//
//#include <assert.h>
//int main(void) {
//    char *s = "ls | cat -e && echo ok; ls -l";
//    char *r = mx_get_op_name(s);
//    assert(strcmp(r, ";") == 0);
//
//    char *s1 = "ls | cat -e && echo ok & ls -l";
//    char *r1 = mx_get_op_name(s1);
//    assert(strcmp(r1, "&") == 0);
//
//    char *s2 = "ls | cat -e && echo ok";
//    char *r2 = mx_get_op_name(s2);
//    assert(strcmp(r2, "&&") == 0);
//
//    char *s3 = "ls | cat -e || echo ok";
//    char *r3 = mx_get_op_name(s3);
//    assert(strcmp(r3, "||") == 0);
//
//    char *s4 = "ls | cat -e ";
//    char *r4 = mx_get_op_name(s4);
//    assert(strcmp(r4, "|") == 0);
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
