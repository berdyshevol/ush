//
// Created by Олег on 2/13/20.
//

#include "parser.h"

static void _extract_first_wordchain(char **str, char **f_wordchain);
static void _extract_splitter(char **str, char **splitter);
static void _extract_rest_wordchains(char **str, char **r_wordchains);

// ----    API Functions
void mx_parse_words_sequence(char *exp, char **f_wordchain, char **splitter, char **r_wordchains) {
    char *str = NULL;

    *f_wordchain = NULL;
    *splitter = NULL;
    *r_wordchains = NULL;
    if (exp == NULL)
        return ;
    if (!mx_is_closed_expression(exp))     // TODO: we do not need it
        return ;
    str = strdup(exp);
    _extract_first_wordchain(&str, f_wordchain);
    _extract_splitter(&str, splitter);
    _extract_rest_wordchains(&str, r_wordchains);
    free(str);
}

char *mx_first_word(char *exp) {
    char *fwc = NULL; // first word-chain
    char *spl = NULL; // splitter of whitespaces
    char *rwc = NULL; // rest word-chains

    mx_parse_words_sequence(exp, &fwc, &spl, &rwc);
    free(spl);
    free(rwc);
    return fwc;
}

bool mx_is_last_word(char *exp) {
    return exp == NULL;
}

char *mx_rest_words(char *exp) {
    char *fwc = NULL; // first word-chain
    char *spl = NULL; // splitter of whitespaces
    char *rwc = NULL; // rest word-chains

    mx_parse_words_sequence(exp, &fwc, &spl, &rwc);
    mx_strdel(&spl);
    mx_strdel(&fwc);
    return rwc;
}

// ----- statics
static void _extract_first_wordchain(char **str, char **f_wordchain) {
    int i; // for loop iterator
    char *temp = NULL;
    *f_wordchain = NULL;
    e_mode mode = unquote;
    //идти пока не встретим неэкраннированный whitespace
    for (i = 0; (*str)[i] != '\0'; i++) {
        mx_change_mode(&mode, *str, i);
        if (mode == unquote
            && mx_is_whitespace((*str)[i])
            && mx_count_esc(*str, i) % 2 == 0
            )
            break ;
    }

    //изменить стр и вернуть первый вордчеин
    if (i != 0) {
        *f_wordchain = strndup(*str, i);
        temp = *str;
        *str = strndup(*str + i, strlen(*str) - i);
        free(temp);
    }
}
//static void _extract_first_wordchain(char **str, char **f_wordchain) {
//    int count_slashes = 0;
//    int i; // for loop iterator
//    char *temp = NULL;
//    *f_wordchain = NULL;
//
//    //идти пока не встретим неэкраннированный whitespace и выражение слева замкнутое
//    for (i = 0; (*str)[i] != '\0'; i++) {
//        if ((*str)[i] == '\\')
//            count_slashes++;
//        else if (mx_is_whitespace((*str)[i])) {
//            if (count_slashes % 2 == 0) { // whitespace case
//                // break if expression is closed
//                char *extract = strndup(*str, i);
//                if (mx_is_closed_expression(extract)) {
//                    free(extract);
//                    break;
//                }
//                else
//                    free(extract);
//            }
//            count_slashes = 0;
//        }
//    }
//    //изменить стр и вернуть первый вордчеин
//    if (i != 0) {
//        *f_wordchain = strndup(*str, i);
//        temp = *str;
//        *str = strndup(*str + i, strlen(*str) - i);
//        free(temp);
//    }
//}

static void _extract_splitter(char **str, char **splitter) {
    int i;
    char *temp = NULL;
    *splitter = NULL;

    for (i = 0; (*str)[i] != '\0'; i++) {
        if (!mx_is_whitespace((*str)[i]))
            break;
    }
    if (i != 0) {
        *splitter = strndup(*str, i);
        temp = *str;
        *str = strndup(*str + i, strlen(*str) - i);
        free(temp);
    }
}

static void _extract_rest_wordchains(char **str, char **r_wordchains) {
    if (**str == '\0') // that is length == 0
        *r_wordchains = NULL;
    else
        *r_wordchains = strdup(*str);
}


//
//
//#include <assert.h>
//void assert2str (char *s1, char *s2){
//    if (s1 == NULL || s2 == NULL)
//        assert(s1 == s2);
//    else
//        assert(strcmp(s1, s2) == 0);
//}
//
//int main(void) {
//    printf("Test mx_parse_words_sequence\n");
//
//    char *s[] =        {"\\\"oo'o o'ooo\"q  \"qqqq qqq",
//                        " hello ", "hello  ", "hello world",
//                        "\\ hello\\ \t oleg", "$(hi oleg)\\  hi"
//                        };
//    char *test_fwc[] = {"\\\"oo'o o'ooo\"q  \"qqqq",
//            NULL,      "hello",    "hello",       "\\ hello\\ ",       "$(hi oleg)\\ " };
//    char *test_sp[] =  { " ",
//            " ",      "  ",      " " ,          "\t " ,                " "};
//    char *test_rwc[] = {"qqq",
//            "hello ",  NULL,       "world",      "oleg",                "hi" };
//
//    for (int i = 0; i < 5; i++) {
//        char *fwc;
//        char *spl;
//        char *rwc;
//        char *str = strdup(s[i]);
//
//        printf("Test %d '%s' -> ", i+1, str);
//        mx_parse_words_sequence(str, &fwc, &spl, &rwc);
//        printf("<%s> <%s> <%s>\n", fwc, spl, rwc);
//        assert2str (fwc, test_fwc[i]);
//        assert2str (spl, test_sp[i]);
//        assert2str (rwc, test_rwc[i]);
//        free(str);
//        free(fwc);
//        free(spl);
//        free(rwc);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
