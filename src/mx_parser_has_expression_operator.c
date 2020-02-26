#include "parser.h"

bool mx_has_expression_operator(char *exp, char *operator) {
    char *p = NULL;
    bool res = false;

    p = mx_smart_find(exp, operator);
    if (p) {
        char *tmp = mx_strndup((const char *)exp, p - exp);
        if (mx_is_closed_expression(tmp))
            res = true;
        free(tmp);
    }
    return res;
}

//#include <assert.h>
//
//int main(void) {
//    char *s = "H'el'lo;World";
//    assert(mx_has_expression_operator(s, ";"));
//
//    char *s1 = "Hel\\ 'lo' || World";
//    assert(mx_has_expression_operator(s, ";"));
//
//    char *s11 = "Hello\\ W`orld || Ol`eg";
//    assert(mx_has_expression_operator(s11, ";") == false);
//    printf("SUCCESS\n");
//
//    system("leaks -q parser");
//
//    return 0;
//}

