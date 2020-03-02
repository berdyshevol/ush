//
// Created by Oleg Berdyshev on 2/11/20.
//

#include "parser.h"

//int *is_delim(int i, char *s, int count_slash){
//    char *delim[] = {" ", "$", "\"", "\'", "`", "("};
//    int length[] =  {1,    1,   2,    2,    1,   1};
//    int len = 6;
//
//    for (int j = 0; j < len; j++)
//        if (count_slash % 2 == 0) // все слеши погашены
//            if (strncmp( s + i, delim[j], length[j]) == 0)
//                return j;
//    return -1;
//}
//
//static int count_slashes(int i, char *s) {
//    int count = 0;
//    for (int j = i - 1; j >= 0; j--) {
//        if(s[j] == '\\')
//            count++;
//    }
//    return count;
//}


//static int  find_first_nonwhitespace_char(char *s) {
//    if (s == NULL)
//        return -1;
//    int i = 0;
//
//    while (s[i]) {
//        if (mx_isspace(*s))
//            i++;
//        else
//            return i;
//    }
//    return -1;
//}

//static bool is_parameter(char *s) {
//    if (s == NULL)
//        return false;
//    return strlen(s) > 2 // $<<char>>
//          && s[0] == '$'
//          && !(s[1] == '{' || s[1] == '(');
//}

///**  возвращает 0, если нет параметра, и номер, где заканчивается параметр
// */
//static bool get_parameter(int start, char *s, int *end) {
//    *end = -1;
//    if (s == NULL) {
//        return false;
//    }
//    if (s[start] != '$') { // если не начинается с  $
//        return false;
//    }
//    if (mx_is_single_char(s[start + 1])) { //  односимвольные параметры
//        *end = start + 1;
//        return true;
//    }
//    // начало либо _ либо буква
//    if (!(s[start + 1] == '_' || mx_isalpha(s[start + 1]))) {
//        return false;
//    }
//    for (int i = start + 2; s[i]; i++) {
//        if (!(s[i] == '_' || mx_isalpha(s[i]) || mx_isdigit(s[i]))) {
//            *end = i - 1;
//            return true;
//        }
//    }
//    return false;
//}

/**
 * возвращает первое  слово:
 * строку до ' " $ ` { или пробела. При этом урезать '\'
 * '..' ".." $() ${} `..`
 * $name до первого пробела
 */
//void mx_first_word_(char *exp, char **first_word, char **rest_exp) {
//    int trim = -1;
//    int id = -1;
//    int end = -1;
//    char *fw = NULL;
//    char *re = NULL;
//
//    //    trim
//    trim = find_first_nonwhitespace_char(exp);
//    if (is_parameter(exp[trim])) {  // case $name.. not ${name}
//        if (get_parameter(trim, exp, &end)) {
//            fw = strndup(exp, end);
//            re = strndup(exp + end + 1, strlen(exp) - end - 1);
//        }
//        else {
//
//        }
//    }
////    else if (is openning in string) {
//    else if((id = mx_is_opening(trim, exp[trim], 0))) {
////        if (is closing)
//         if (mx_is_closed_expression(exp[trim])) {
////            get the whole closed expression
//         }
//
//         else {
////            get string before first real space
//        }
//    }
//    else {
////        get string before first real space
//    }

//}

//
//void mx_get_first_word(char *exp, char **first_word, char **rest_exp) {
////    int len = strlen(spacial_symbol);
////    char s1[2];
////    char *s2;
////    char *res = NULL;
////    char *exp = mx_trim(raw_exp);
////
////    s1[0] = spacial_symbol[0];
////    s1[1] = '\0';
////    s2 = mx_car(exp, s1);
////    free(exp);
////    res = s2;
////    for (int i = 0; i < len; i++) {
////        s1[0] = spacial_symbol[i];
////        s2 = mx_car(exp, s1);
////        if (s2 != NULL && res != NULL && strlen(s2) < strlen(res)) {
////            free(res);
////            res = s2;
////        }
////    }
////    return res;
//}


////test char *mx_get_first_word(char *exp)
//#include <assert.h>
//#include <stdio.h>
//int main(void) {
//    char *exp[] = {" hello ", "hello world", " hello$(kdkdk kj",
//                   "${hello} kj", " ${hello} kdkdk", " $(hel${hi}) hello",
//                   " \\$hello ", " \\\\`hello`", " \\\\\\`hello`",
//                   NULL};
//    char *res[] = {"hello", "hello", "hello",
//                   "${hello}", "${hello}", "$(hel${hi})",
//                   " \\ ", "\\\\", "\\\\\\`hello`"};
//    for (int i = 0; exp[i]; i++) {
//        char *fw;
//        char *re;
//        mx_get_first_word(exp[i], &fw, &re);
//        printf("%d) <<%s>> -> <%s> <%s>\n", i+1, exp[i], fw, re);
////        if (fw == NULL || res[i] == NULL)
////            assert(fw == res[i]);
////        else
////            assert(strcmp(fw, res[i]) == 0);
//        free(re);
//        free(fw);
//    }
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
