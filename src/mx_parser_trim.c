#include "parser.h"

// should go with is_spacial_symbol
char mx_whitespace(int i) {
    char spacial_symbol[] = " \n\t"; // trim all these chars without
    if (i >= 0 && i < (int)strlen(spacial_symbol))
        return spacial_symbol[i];
    else
        return '\0';
}

//// slash
//// should go with can_skip
//char mx_slash_plus_symbol(int i) {
//    char *slash_plus_symbol = " "; // skip triming "\ "
//    if (i >= 0 && i < strlen(slash_plus_symbol))
//        return slash_plus_symbol[i];
//    else
//        return '\0';
//}

/**
 * из строки exp берет  левое выражение от оператора op
 * учитывает замыкающие конструкции '..' ".." (..) {..} `..`
 */
char *mx_left_exp(char *exp, char *delim) {
    char *car;
    char *rs;

    if (delim == NULL)
        return strdup(exp);
    mx_split_two_str(exp, delim, &car, &rs);
    free(rs);
    if (strcmp(car, "") == 0) {
        free(car);
        car = NULL;
    }
    return car;
}

/**
 * из строки exp берет правое выражение от оператора op
 * учитывает замыкающие конструкции '..' ".." (..) {..} `..`
 */

char *mx_right_exp(char *exp, char *delim) {
    char *cdr;
    char *ls;

    if (delim == NULL)
        return NULL;
    mx_split_two_str(exp, delim, &ls, &cdr);
    free(ls);
    if (strcmp(cdr, "") == 0) {
        free(cdr);
        cdr = NULL;
    }
    return cdr;
}


/**
 * trim string
 */
char *mx_trim(char *s) {
    int left;
    int right;

    //what can trim going from left
    left = 0;
    while (mx_can_trim(left, s))
        left++;
    //what can trim going from right
    right = strlen(s) - 1;
    while (mx_can_trim(right, s))
        right--;
    return mx_strndup(&s[left], right - left +1);
}

bool mx_is_whitespace(char c) {
    //int len = strlen(spacial_symbol);
    for (int i = 0; mx_whitespace(i) != '\0'; i++)
        if (c == mx_whitespace(i))
            return true;
    return false;
}

//bool mx_can_skip(char c) {
//    //int len = strlen(slash_plus_symbol);
//    for (int i = 0; mx_slash_plus_symbol(i) != '\0'; i++)
//        if (c == mx_slash_plus_symbol(i))
//            return true;
//    return false;
//}



bool mx_can_trim(int i, char *s) {
    if (mx_is_whitespace(s[i])) {
//        if (mx_can_skip(s[i]) && i > 0 && s[i-1] == '\\')
//            return false;
//        else
            return true;
    }
    return false;    
}

//#include <assert.h>
//#include <stdio.h>
//
//// test trim
//int main(void) {
//    printf("test trim\n-------\n");
//
//    char *s[] = { " hello ", "", "",
//            NULL};
//    char *test[] = {};
//
//    for (int i = 0; s[i] != NULL; i++) {
//        char *res = mx_trim(s[i]);
//        printf("'%s'->'%s'\n", s[i], res);
//        if (res == NULL)
//            assert(res == test[i]);
//        else
//            assert(strcmp(res, test[i]) == 0);
//        free(res);
//    }
//
//    printf("\nSUCCESS\n----\n");
//
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
//


//#include <assert.h>
//#include <stdio.h>
//
//// test car and cdr
//int main(void) {
//    printf("test car cdr\n-------\n");
//
//    char *s = "Hello;World";
//    char *op = ";";
//    char *ls = mx_left_exp(s, op);
//    char *rs = mx_right_exp(s, op);
//
//    printf("1) '%s' => car='%s' and cdr='%s'\n", s, ls, rs);
//    assert(strcmp(ls, "Hello") == 0);
//    assert(strcmp(rs, "World") == 0);
//
//    char *s0 = "Hello; ";
//    char *ls0 = mx_left_exp(s0, op);
//    char *rs0 = mx_right_exp(s0, op);
//
//    printf("2) '%s' => car='%s' and cdr='%s'\n", s0, ls0, rs0);
//    assert(strcmp(ls0, "Hello") == 0);
//    assert(rs0 == NULL);
//    free(ls0);
//    free(rs0);
//
//    char *s1 = "Hel\\ lo || World";
//    char *op1 = "||";
//    char *ls1 = mx_left_exp(s1, op1);
//    char *rs1 = mx_right_exp(s1, op1);
//    printf("3) '%s' => car='%s' and cdr='%s'\n", s1, ls1, rs1);
//    assert(strcmp(ls1, "Hel\\ lo") == 0);
//    assert(strcmp(rs1, "World") == 0);
//    free(ls1);
//    free(rs1);
//
//    char *s2 = "Hello || ";
//    char *op2 = "||";
//    char *ls2 = mx_left_exp(s2, op2);
//    char *rs2 = mx_right_exp(s2, op2);
//    printf("4) '%s' => car='%s' and cdr='%s'\n", s2, ls2, rs2);
//    assert(strcmp(ls2, "Hello") == 0);
//    assert(rs2 == NULL);
//    free(ls2);
//    free(rs2);
//
//    char *s3 = "cat | echo || cat";
//    char *op3 = "||";
//    char *ls3 = mx_left_exp(s3, op3);
//    char *rs3 = mx_right_exp(s3, op3);
//    printf("5) '%s' => car='%s' and cdr='%s'\n", s3, ls3, rs3);
//    assert(strcmp(ls3, "cat | echo") == 0);
//    assert(strcmp(rs3, "cat") == 0);
//
//    char *s4 = "cat | echo || cat";
//    char *op4 = "|";
//    char *ls4 = mx_left_exp(s4, op4);
//    char *rs4 = mx_right_exp(s4, op4);
//    printf("6) '%s' => car='%s' and cdr='%s'\n", s4, ls4, rs4);
//    assert(strcmp(ls4, "cat") == 0);
//    assert(strcmp(rs4, "echo || cat") == 0);
//
//    printf("\nSUCCESS\n----\n");
//
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
//
