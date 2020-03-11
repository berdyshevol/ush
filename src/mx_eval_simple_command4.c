//
// Created by Oleg Berdyshev on 3/11/20.
//

#include "evaluator.h"

// ----    API Function

void mx_copy(char c, char *newexp, int *index) {
    newexp[*index] = c;
    (*index)++;
}

