//
// Created by Oleg Berdyshev on 2/19/20.
//
#include "parser.h"

int mx_count_esc(char *exp, int position) {
    int count = 0;
    for (int i = position - 1; i >= 0; i--) {
        if (exp[i] == '\\')
            count++;
        else
            break;
    }
    return count;
}

char *mx_strstr_esc(char *exp, char *substr) {
    int len  = strlen(exp);
    char *p = NULL;
    int count = 0;

    for (int i = 0; i < len; i++) {
        p = strstr(exp + i, substr);
        if (p) {
            if (mx_count_esc(exp, p - exp) % 2 == 0)
                return p;
        }
        count = 0;
    }
    return NULL;
}

void mx_change_mode(e_mode *mode, char *exp, int pos) {
    switch (*mode) {
        case unquote:
            if (exp[pos] == '"')
                if (mx_count_esc(exp, pos) % 2 == 0)
                    *mode = dquote;
            if (exp[pos] == '\'')
                if (mx_count_esc(exp, pos) % 2 == 0)
                    *mode = quote;
            break;
        case dquote:
            if (exp[pos] == '"')
                if (mx_count_esc(exp, pos) % 2 == 0)
                    *mode = unquote;
            break;
        case quote:
            if (exp[pos] == '\'')
                *mode = unquote;
            break;
    }
}

////mx_strstr_esc
//#include <assert.h>
//int main(void) {
//    char *exp[] =   {"0123$   ", "0123\\$67$  ", "0123\\\\$7$  ", NULL};
//    char *test[] =  {    "$   ",          "$  ",         "$7$  ", NULL};
//
//    for (int i = 0; exp[i]; i++) {
//        char *s = mx_strstr_esc(exp[i], "$");
//        printf("%d) '%s' -> '%s'\n", i + 1, exp[i], s);
//        if (s == NULL)
//            assert(s == test[i]);
//        else
//            assert(strcmp(s, test[i]) == 0);
//
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}

