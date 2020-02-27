//
// Created by Олег on 2/13/20.
//

#include "parser.h"

int controling_char(char c) {
    return c == '$' || c ==  '\'' || c == '\"' || c == '`' || c == '~';
}

bool has_string(char *exp, char **firstword, e_word_type *type, char **restwords) {
    int i = 0;
    bool res = false;

    while (!controling_char(exp[i]))
        i++;
    if (i != 0) {
        *firstword = strndup(exp, i);
        res = true;
    }
    if (strlen(exp) != i + 1) {
        *restwords = strndup(exp + i, strlen(exp) - i);
    }
    return res;
}

void _extract_escseq(char *exp, char **firstword, e_word_type *type, char **restwords) {
    int n;

    *firstword = strndup(exp, 2);
    n = strlen(exp) - strlen(*firstword);
    if (n > 0)
        *restwords = strndup(exp + 2, n);
    else
        *restwords = NULL;
    *type = esc_type;
}

void _expract_tildaexp(char *exp, char **firstword, e_word_type *type, char **restwords) {
    char *fwc = NULL;
    char *spl = NULL;
    char *rwc = NULL;
    char *join = NULL;
    size_t len;

    mx_parse_words_sequence(exp, &fwc, &spl, &rwc);
    *firstword = fwc;
    len = (spl == NULL) ? 0 : strlen(spl);
    len += (rwc == NULL) ? 0 : strlen(rwc);
    if (len > 0) {
        join = mx_strjoin(spl, rwc);
    }
    *restwords =join;
    *type = file_expansion_type;

    free(spl);
    free(rwc);
}

void _extract_(char *exp, char **firstword, e_word_type *type, char **restwords, char ch) {
//    char *p = NULL;
//    *firstword = NULL;
//    *restwords = NULL;
//
//    p = mx_smart_find(exp, ch);
//    if (p != NULL) {
//        int n = p - exp;
//        if (n > 0) {
//            *firstword = strndup(exp, n);
//        }
//    } else
//        *type = unclosed_exp_type;
}

//void mx_parse_wordchain(char *exp, char **firstword, e_word_type *type, char **restwords) {
//    *firstword = NULL;
//    *type = string_type;
//    *restwords = NULL;
//    int i = 0;
//
//    if (exp == NULL)
//        return ;
//    if (exp[0] == '\\')
//        _extract_escseq(exp, firstword, type, restwords);
//    else if (exp[0] == '~') {
//        _expract_tildaexp(exp, firstword, type, restwords);
//    }
//    else if (exp[0] == '\"') {
//        _extract_(exp, firstword, type, restwords, '\"');
//        if (type != unclosed_exp_type)
//            type = dquote_type;
//    }
//
//}
//
//int main(void) {
//    char *exp = "\"~/hi\" oleg";
//    char *fwc, *rwc;
//    e_word_type type;
//    _expract_tildaexp(exp, &fwc, &type, &rwc);
//    return 0;
//}
