//
// Created by Олег on 2/13/20.
//

#include "parser.h"

// ----    API Functions
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

