#include "parser.h"

bool is_ampersand_pipe(char *exp, char *p, char *op) {
    // проверить, что это точно & а не && или >&
    if (strcmp(op, "&") == 0) // if op == &
        if (*(p + 1) == '&'
            || (p != exp && *(p - 1) == '&')
            || (p != exp && *(p - 1) == '>')) {
            //s += s - p;
            return true;
        }
    // проверить, что это точно | а не || или |&
//            if (strcmp(mx_get_name_by_id(pipe_operator), op) == 0) // if op == |
    if (strcmp(op, "|") == 0) // if op == |
        if (*(p + 1) == '|'
            || (p != exp && *(p - 1) == '|')
            || *(p + 1) == '&') {
            //s += s - p;
            return true;
        }
    return false;
}

/**
 * находит первое вхождение оператора op в выражении exp, 
 * но так, чтобы слева было замкнутое выражение
 */
char *mx_smart_find(char *exp, char *op) {
    char *p = NULL;
    char *s = exp;
    for (; s != '\0'; s = exp + (p - exp + 1)) {
        p = strstr(s, op);
        if (p) {
            if (is_ampersand_pipe(exp, p, op))
                continue;
            char *tmp = mx_strndup((const char *) exp, p - exp);
            if (mx_is_closed_expression(tmp)) {
                free(tmp);
                return p;
            }
            free(tmp);
        }
        else
            break;
    }
    return NULL;
}

//#include <assert.h>
//#include <stdio.h>
//
//int main(void) {
//    printf("smart find\n");
//    char *exp = "Hello\\ World || Hello | World";
//    char *op = "||";
//    char *res = mx_smart_find(exp, op);
//    printf("1. '%s'->'%s'\n", exp, res);
//    assert(strcmp(res, "|| Hello | World") == 0);
//
//    char *exp1 = "He$(llo\\ Wor)ld || Hello | World";
//    char *op1 = "||";
//    char *res1 = mx_smart_find(exp1, op1);
//    printf("2. '%s'->'%s'\n", exp1, res1);
//    assert(strcmp(res1, "|| Hello | World") == 0);
//
//    char *exp11 = "He${llo\\ World && He}llo && World";
//    char *op11 = "&&";
//    char *res11 = mx_smart_find(exp11, op11);
//    printf("3. '%s'->'%s'\n", exp11, res11);
//    assert(strcmp(res11, "&& World") == 0);
//
//    char *exp111 = "He$(llo\\ Wo)r`ld || He`llo || World";
//    char *op111 = "||";
//    char *res111 = mx_smart_find(exp111, op111);
//    printf("4. %s'->'%s'\n", exp111, res111);
//    assert(strcmp(res111, "|| World") == 0);
//
//    char *exp1111 = "He$(llo\\ Wo)r`ld || Hello || W`orld";
//    char *op1111 = "||";
//    char *res1111 = mx_smart_find(exp1111, op1111);
//    printf("5. '%s'->'%s'\n", exp1111, res1111);
//    assert(res1111 == NULL);
//
//    char *exp2 = "Hello\\ World || Hello | World";
//    char *op2 = "|";
//    char *res2 = mx_smart_find(exp2, op2);
//    printf("6. '%s'->'%s'\n", exp2, res2);
//    assert(strcmp(res2, "| World") == 0);
//
//    char *exp3 = "Hello\\ World | Hello || World";
//    char *op3 = "|";
//    char *res3 = mx_smart_find(exp3, op3);
//    printf("7. '%s'->'%s'\n", exp3, res3);
//    assert(strcmp(res3, "| Hello || World") == 0);
//
//    char *exp4 = "Hello\\ World && Hello & World";
//    char *op4 = "&";
//    char *res4 = mx_smart_find(exp4, op4);
//    printf("8. '%s'->'%s'\n", exp4, res4);
//    assert(strcmp(res4, "& World") == 0);
//
//    char *exp5 = "Hello\\ World & Hello && World";
//    char *op5 = "&";
//    char *res5 = mx_smart_find(exp5, op5);
//    printf("9. '%s'->'%s'\n", exp5, res5);
//    assert(strcmp(res5, "& Hello && World") == 0);
//
//    printf("SUCCESS\n");
//
//    system("leaks -q ush");
//
//    return 0;
//}
