#include "ush.h"

void mx_get_str_spase(char *str, char repl, char **tmp) {
    char *res = mx_strdup(*tmp);
    char *replace = mx_strndup(&repl, 1);

    if (mx_get_substr_index(*tmp, str) != -1 ) {
        mx_strdel(tmp);
        *tmp = mx_replace_substr(res, str, replace);
    }
    mx_strdel(&res);
    mx_strdel(&replace);  
}

void mx_more_escapes(char **tmp) {
    mx_get_str_spase("\\x09", '\t', tmp);
    mx_get_str_spase("\\x00", '\0', tmp);
    mx_get_str_spase("\\x07", '\a', tmp);
    mx_get_str_spase("\\x08", '\b', tmp);
    mx_get_str_spase("\\x0a", '\n', tmp);
    mx_get_str_spase("\\x0b", '\v', tmp);
    mx_get_str_spase("\\x0c", '\f', tmp);
    mx_get_str_spase("\\x0d", '\r', tmp);
    mx_get_str_spase("\\x1b", '\033', tmp);
    mx_get_str_spase("\\011", '\t', tmp);
    mx_get_str_spase("\\000", '\0', tmp);
    mx_get_str_spase("\\007", '\a', tmp);
    mx_get_str_spase("\\010", '\b', tmp);
    mx_get_str_spase("\\012", '\n', tmp);
    mx_get_str_spase("\\013", '\v', tmp);
    mx_get_str_spase("\\014", '\f', tmp);
    mx_get_str_spase("\\015", '\r', tmp);
    mx_get_str_spase("\\0", '\0', tmp); 
}

bool mx_check_sound(char *out) {
    for (int i = 0; out[i] != '\0'; i++)
        if (out[i] != '\a')
            return false;
    return true;
}
