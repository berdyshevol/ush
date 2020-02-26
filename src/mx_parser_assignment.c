//
// Created by Олег on 2/13/20.
//

#include "parser.h"

// ----------- for mx_is_valid_parname
bool mx_isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z');
}

bool mx_is_single_char(char c) {
    return c == '*' || c == '@' || c == '#' || c == '?'
           || c == '-' || c == '$' || c == '!';
}

bool mx_is_valid_parname(char *exp) {
    if (exp == NULL)
        return false;
    if (mx_is_single_char(exp[0])) {
        if (exp[1] == '\0')
            return true;
        else
            return false;
    }
    if (!(exp[0] == '_' || mx_isalpha(exp[0])))
        return false;
    for (int i = 1; exp[i]; i++) {
        if (!(exp[i] == '_' || mx_isalpha(exp[i]) || mx_isdigit(exp[i])))
            return false;
    }
    return true;
}

bool mx_is_valid_myparname(char *exp) {
    if (exp == NULL)
        return false;
    if (!(exp[0] == '_' || mx_isalpha(exp[0])))
        return false;
    for (int i = 1; exp[i]; i++) {
        if (!(exp[i] == '_' || mx_isalpha(exp[i]) || mx_isdigit(exp[i])))
            return false;
    }
    return true;
}

bool mx_has_assignment(char *exp) {
    char *p = NULL;
    char *parname = NULL;
    //char *trim = NULL;
    bool res = false;

    //trim = mx_trim(exp);
    p = strstr(exp, "=");
    if (p != NULL) {
        parname = strndup(exp, p - exp);
        if (mx_is_valid_myparname(parname))
            res = true;
        free(parname);
    }
    //free(trim);
    return res;
}

//// test valid name
//#include <assert.h>
//int main(void) {
//    printf("Test valid name\n");
//    int number = 6;
//    char *name[] = {"_name", "lsmsm", "kd7ak", "3jkksdj", "kd_kdkd", "12",
//                    NULL};
//    char test[] = {true,      true,    true,    false,     true, false, false};
//    for (int i = 0; i < number; i++) {
//        printf("test %d %s (%d)\n", i+1, name[i], test[i]);
//        bool res = mx_is_valid_parname(name[i]);
//        assert(res == test[i]);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}

// //test has param name
//#include <assert.h>
//int main(void) {
//    printf("Test has param name\n");
//    int number = 6;
//    char *name[] = {" _name=", " lsmsm =", "\\ kd7ak=", "3jkksdj=", " kd3kdkd= ", "?=", NULL};
//    char test[] = {true,        false,        false,    false,       true,        false};
//    for (int i = 0; i < number; i++) {
//        printf("test %d\n", i+1);
//        bool res = mx_has_assignment(name[i]);
//        assert(res == test[i]);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}