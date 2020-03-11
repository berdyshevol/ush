#include "parser.h"

static bool cmdsubs_typetwo_helper(char *exp, char *find_begin, t_args *args) {
    args->start = find_begin - exp;
    char *find_end = mx_strstr_esc(find_begin + 1, "`");
    if (find_end == NULL) {
        mx_print_oddnumberofquotes();
        return false;
    }
    args->end = find_end - exp;
    args->name = strndup(exp + args->start + 1, args->end - args->start - 1);
    return true;
}

// Do not use this function alone
e_return mx__cmdsubs_type_two(char *exp, int i, t_args *args) {
    char *find_begin = &exp[i];
    if (mx_count_esc(exp, find_begin - exp) % 2 != 0)
        return continue_loop;
    if (cmdsubs_typetwo_helper(exp, find_begin, args))
        return return_true;
    else
        return break_loop;
}



