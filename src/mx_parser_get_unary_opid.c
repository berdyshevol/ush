#include "parser.h"

static char *opening_chars_unary_op[] = {"'", "\"", "${", "$(", "$", "`", "~",  NULL};
static char *closing_chars_unary_op[] = {"'", "\"", "}",  ")",  "",  "`",  "", NULL};

static bool mx_has_open_closing_exp(char *exp, char *open_exp, char *closing_exp);
    
/**
 * выражение => номер оператора (унарного)
 * приоритер поиска следующий
 * 1.   '..'
 * 2.   ".."
 * 2.   ${..}
 * 3.   $(..)
 * 4.   $name
 * 5.   `..`
 * 6.   ~
 */
e_operator_id mx_get_unary_opid(char *exp) {
    char *trimmed;
    e_operator_id res = no_operator;

    if (!mx_is_closed_expression(exp))
        return unclosed_expression;
    
    trimmed = mx_trim(exp);
    for (int i = 0; opening_chars_unary_op[i]; i++) {
        if (mx_has_open_closing_exp(trimmed,
                                    opening_chars_unary_op[i], 
                                    closing_chars_unary_op[i])) {
            res = all_binary_operators + i + 1;
            // if (res == tilda) {
            //     if (!mx_is_valid_pathname(trimmed + 1))
            //         res = no_operator;
            // }
            break;
        }
    }
    free(trimmed);
    return res;
}

char *mx_extract_unary_operand(char *exp) {
    e_operator_id opid = mx_get_unary_opid(exp);
    if (opid == no_operator || opid == unclosed_expression)
        return NULL;

    char *trimmed = mx_trim(exp);
    char *res = NULL;
    int left_len = strlen(opening_chars_unary_op[opid - all_binary_operators - 1]);
    int right_len = strlen(closing_chars_unary_op[opid - all_binary_operators - 1]);
    int len = strlen(trimmed);

    res = mx_strndup(trimmed + left_len, len - left_len - right_len);
    free(trimmed);
    return res;
}

bool mx_is_valid_pathname(char *exp) {
    if (exp != NULL)
        return false;

    if (exp[0] == '/')
        return true;
    else
        return false;
}

static bool mx_has_open_closing_exp(char *exp, char *open_exp, char *closing_exp) {
    char *trimmed = NULL;
    char *start_str = NULL;
    char *end_str = NULL;
    bool res = false;
    int len = 0;

    trimmed = mx_trim(exp);
    start_str = mx_strndup(trimmed, strlen(open_exp));
    if (strcmp(start_str, open_exp) == 0) {
        len = strlen(closing_exp);
        end_str = mx_strndup(trimmed + (strlen(trimmed) - len), len);
        if (strcmp(end_str, closing_exp) == 0)
            res = true;
        free(end_str);
    }
    free(start_str);
    free(trimmed);
    return res;
}
//
// #include <assert.h>
// int main(void) {
//     printf("Test open close chars\n");
//     char *open[] = {"$(",  "$(", "$(",
//                     "$(",  "$(", "$(",
//                      "\"", "\"", "\"" ,
//                      "$",  "~",  "`"};
//     char *closing[] = {")",  ")",  ")",
//                        ")",  ")",  ")",
//                        "\"", "\"", "\"",
//                        "",   "",   ""};
//     char *str[] = {"$(Hello)",     "$(Hello",     "$Hello)",
//                    "  $(Hello)  ", "  $Hello)  ", "  $(Hello ",
//                    "\"$(Hello)\"", "$(Hello)\"",  "\"$(Hello)",
//                    "$name",        " ~/name ",    " `cmd` ",
//                    NULL};
//     bool res[] = {true, false, false,
//                   true, false, false,
//                   true, false, false,
//                   true, true, true};
//     for (int i = 0; str[i]; i++) {
//         bool b = mx_has_open_closing_exp(str[i], open[i], closing[i]);
//         printf("%d) <%s> <%s> <<%s>> -> %d\n",i+1, open[i], closing[i], str[i], b);
//         assert(b == res[i]);
//     }
//     printf("SUCCESS\n");
//
//     printf("test is valid param name\n");
//     assert(mx_is_valid_parname("nnas_KSJDK") == true);
//     assert(mx_is_valid_parname("n$nas_KSJDK") == false);
//     assert(mx_is_valid_parname(" n$nas_KSJDK") == false);
//     printf("SUCCESS\n");
//
//     printf("test mx_get_unary_opid\n");
//
//     char *s[] = {" 'hello' ", " 'hello ",  " \"hello\" ", " \"hello ",
//                  " ${hello}", "${hello",   "  $(hello)",  "$(hello",
//                  "  $hello",  "  hello ",  " `hello` ",   " hello` ",
//                  "  ~",       " ~name"  ,
//                  NULL};
//     e_operator_id b[] = {quote_op, unclosed_expression, doublequote, unclosed_expression,
//                          dollar_curly_bracket, unclosed_expression, dollar_parathesese, unclosed_expression,
//                          dollar_name, no_operator, backquote, unclosed_expression,
//                          tilda, tilda};
//     for (int i = 0; s[i]; i++) {
//         e_operator_id res = mx_get_unary_opid(s[i]);
//         printf("%d) <<%s>> -> %d (%d)\n",i+1, s[i], res, b[i]);
//         assert(b[i] - res == 0);
//     }
//     printf("SUCCESS\n");
//
//     printf("test extract unary operand\n");
//     char *extract[] = {"hello", NULL,  "hello",  NULL,
//                        "hello", NULL,  "hello",  NULL,
//                        "hello", NULL,  "hello", NULL,
//                        "",      "name"  ,
//                     NULL};
//     for (int i = 0; s[i]; i++) {
//         char *res = mx_extract_unary_operand(s[i]);
//         printf("%d) <<%s>> -> %s (%s)\n",i+1, s[i], res, extract[i]);
//         if (res != NULL)
//             assert(strcmp(res, extract[i]) == 0);
//         else
//             assert(extract[i] == NULL);
//         free(res);
//     }
//     printf("\nSUCCESS\n----\n");
//     system("leaks -q ush_metacicle_evaluator");
//     return 0;
// }
