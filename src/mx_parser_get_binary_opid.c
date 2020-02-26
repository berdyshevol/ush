#include "parser.h"
/**
 * выражение => номер оператора (бинарного)
 * приоритер поиска следующий
 * 1.   ;    &
 * 2.   ||   &&
 * 3.   |    |&
 * 4.   =
 */
e_operator_id mx_get_binary_opid(char *exp) {
    if (!mx_is_closed_expression(exp)) {
        return unclosed_expression;
    }
    for (int i = 0; i < all_binary_operators; i++) {
        char *op_name = mx_get_name_by_id(i);
        if (mx_has_expression_operator(exp, op_name)) {
            return i;
        }
    }
    if (mx_has_assignment(exp))
        return parameter_assignment;
    return no_operator;
}


// #include <assert.h>
// int main(void) {
//    printf("Test mx_get_binary_opid and get name by id\n");
//    char *s = "`Hello` || World";
//    char *res = mx_get_name_by_id(mx_get_binary_opid(s));
//    printf("1. '%s' - '%s'\n", s, res);
//    assert(strcmp(res, "||") == 0);
//
//    char *s1 = "`Hello || Wo`rld";
//    char *res1 = mx_get_name_by_id(mx_get_binary_opid(s1));
//    printf("2. '%s' - '%s'\n", s1, res1);
//    assert(res1 == NULL);
//
//    char *exp2 = "Hello\\ World || Hello | World";
//    char *op2 = "||";
//    char *res2 = mx_get_name_by_id(mx_get_binary_opid(exp2));
//    printf("3. '%s'->'%s'\n", exp2, res2);
//    assert(strcmp(res2, op2) == 0);
//
//    char *exp3 = "Hello\\ World | Hello||World";
//    char *op3 = "||";
//    char *res3 = mx_get_name_by_id(mx_get_binary_opid(exp3));
//    printf("4. '%s'->'%s'\n", exp3, res3);
//    assert(strcmp(res3, op3) == 0);
//
//    char *exp4 = "Hello\\ World & Hello& World";
//    char *op4 = "&";
//    char *res4 = mx_get_name_by_id(mx_get_binary_opid(exp4));
//    printf("5. '%s'->'%s'\n", exp4, res4);
//    assert(strcmp(res4, op4) == 0);
//
//    char *exp5 = "Hello\\ World | Hello | World";
//    char *op5 = "|";
//    char *res5 = mx_get_name_by_id(mx_get_binary_opid(exp5));
//    printf("6. '%s'->'%s'\n", exp5, res5);
//    assert(strcmp(res5, op5) == 0);
//
//    printf("SUCCESS\n---------\n");
//
//    system("leaks -q ush_metacicle_evaluator");
//
//    return 0;
// }
