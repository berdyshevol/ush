#include "parser.h"
/**
 * return:
 *      string
 *      quote
 *      doublequote
 *      dollar_curly_bracket
 *      dollar_parathesese
 *      dollar_name
 *      backquote
 *      tilda
 *
 * or else
 *      no_operator
 *      unclosed_expression
 */
//e_operator_id mx_get_word_id(char *exp) {
//    e_operator_id res;
//
//    res = mx_get_unary_opid(exp);
//    // check if it is a string
//    if (res == no_operator) {
//        char *s1 = mx_trim(exp);
//        char *s2 = mx_left_exp(s1, " ");
//        if (s2 != NULL) {
//            if (strcmp(s1, s2) == 0) {
//                res = string;
//            }
//            free(s2);
//        }
//        free(s1);
//    }
//    return res;
//}

//e_operator_id mx_get_op_id(char *exp) {
//    e_operator_id res;
//
//    if (!mx_is_closed_expression(exp)) {
//        res = unclosed_expression;
//    }
//    else {
//        // if binary operator
//        res = mx_get_binary_opid(exp);
//        // if unary operator
//        if (res == no_operator) {
//            res = mx_get_unary_opid(exp);
//        }
//        // if string
//        if (res == no_operator && mx_is_closed_expression(exp)) {
//            char *s1 = mx_trim(exp);
//            char *s2 = mx_left_exp(s1, " ");
//            if (s2 != NULL) {
//                if (strcmp(s1, s2) == 0) {
//                    res = string;
//                }
//                free(s2);
//            }
//            free(s1);
//        }
//    }
//    return res;
//}

// #include <assert.h>
// int main(void) {
////    printf("Test mx_get_op_id and get name by id\n");
////    char *s = "`Hello` || World";
////    char *res0 = mx_get_name_by_id(mx_get_op_id(s));
////    printf("1. '%s' - '%s'\n", s, res0);
////    assert(strcmp(res0, "||") == 0);
////
////    char *s1 = "`Hello || Wo`rld";
////    char *res1 = mx_get_name_by_id(mx_get_op_id(s1));
////    printf("2. '%s' - '%s'\n", s1, res1);
////    assert(res1 == NULL);
////
////    char *exp2 = "Hello\\ World || Hello | World";
////    char *op2 = "||";
////    char *res2 = mx_get_name_by_id(mx_get_op_id(exp2));
////    printf("3. '%s'->'%s'\n", exp2, res2);
////    assert(strcmp(res2, op2) == 0);
////
////    char *exp3 = "Hello\\ World | Hello||World";
////    char *op3 = "||";
////    char *res3 = mx_get_name_by_id(mx_get_op_id(exp3));
////    printf("4. '%s'->'%s'\n", exp3, res3);
////    assert(strcmp(res3, op3) == 0);
////
////    char *exp4 = "Hello\\ World & Hello& World";
////    char *op4 = "&";
////    char *res4 = mx_get_name_by_id(mx_get_op_id(exp4));
////    printf("5. '%s'->'%s'\n", exp4, res4);
////    assert(strcmp(res4, op4) == 0);
////
////    char *exp5 = "Hello\\ World | Hello | World";
////    char *op5 = "|";
////    char *res5 = mx_get_name_by_id(mx_get_op_id(exp5));
////    printf("6. '%s'->'%s'\n", exp5, res5);
////    assert(strcmp(res5, op5) == 0);
//    printf("Test mx_get_word_id\n");
//    char *exp[] = {"  'name' ",     "\"name\" ",     " $(name)",
//                   " `cmd`",        " ~/name",      "$(kdkd",
//                   "ls",            " ls ",         "cat ~/bin",
//                  NULL};
//    e_operator_id res[] = {quote_op, doublequote, dollar_parathesese,
//                           backquote, tilda, unclosed_expression,
//                           string, string, no_operator};
//     for (int i = 0; exp[i]; i++) {
//         e_operator_id opid = mx_get_word_id(exp[i]);
//         printf("%d) <<%s>> %d (%d)\n",i+1, exp[i], opid, res[i]);
//         assert(opid == res[i]);
//     }
//
//    printf("\nSUCCESS\n----\n");
//
//    system("leaks -q ush_metacicle_evaluator");
//
//    return 0;
// }
