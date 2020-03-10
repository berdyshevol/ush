//
// Created by Oleg Berdyshev on 3/10/20.
//

#include "parser.h"

/**
 * @param mode - current mode (unquote, quote, double quote). Mutable parameter
 * @param exp - expression
 * @param pos - current position in the expression which will effect mode.
 */
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
