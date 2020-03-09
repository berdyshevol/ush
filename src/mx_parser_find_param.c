//
// Created by Oleg Berdyshev on 2/19/20.
//

#include "parser.h"

e_return param_expans_typeone(char *exp, char *find_begin, t_args *args) {
    if (find_begin[1] == '{') {
        args->start = find_begin - exp;
        char *find_end = mx_strstr_esc(find_begin, "}");
        if (find_end == NULL) {
            //*end = strlen(exp) - 1;
            mx_print_oddnumberofquotes();
            return break_loop;
        }
        else {
            args->end = find_end - exp;
            args->name = strndup(exp + args->start + 2, args->end  - args->start - 2);
            return return_true;
        }
    }
    return continue_loop;
}

e_return param_expans_typeotwo(char *exp, char *find_begin, t_args *args) {
    args->start = find_begin - exp;
    int i = 1;
    char *temp = strndup(find_begin + 1, i);
    while (mx_is_valid_parname(temp) && find_begin[i]) {
        free(temp);
        i++;
        temp = strndup(find_begin + 1, i);
    }
    free(temp);
    if (args->start != find_begin - exp + i - 1) {
        args->end = find_begin - exp + i - 1;
        args->name = strndup(exp + args->start + 1, args->end - args->start);
        return return_true;
    }
    return continue_loop;
}

e_return param_expans_helper(char *exp, char *find_begin, t_args *args) {
    if (mx_count_esc(exp, find_begin - exp) % 2 != 0)
        return continue_loop;
    e_return res = param_expans_typeone(exp, find_begin, args);
    if (res != continue_loop)
        return res;

    return param_expans_typeotwo(exp, find_begin, args);
}

e_return param_expans(char *exp, int i, e_mode mode, t_args *args) {
    char *find_begin;
    if (exp[i] == '$' && mode != quote) {
        find_begin = &exp[i];
        return param_expans_helper(exp, find_begin, args);
    }
    else
        return continue_loop;
}

bool mx_find_param(char *exp, int *start, int *end, char **name) {
    e_mode mode = unquote;

    t_args *args = args_new();
    for (unsigned long i = 0; i < strlen(exp); i++) {
        mx_change_mode(&mode, exp, i);
        switch (param_expans(exp, i, mode, args)) {
            case continue_loop:
                continue;
            case return_true:
                mx_set(args, start, end, name);
                args_delete(&args);
                return true;
            case break_loop:
                break;
        }
    }
    args_delete(&args);
    mx_reset(start, end, name);
    return false;
}

////test mx_find_param
#include <assert.h>
int main(void) {
    char *exp[] =      {"'$name'$name", "\"$name\"'$name",
                        "012$_a67-80", "0123${12}000", "0\\$ab$ab-",
                        "01\\$ab$12$ab-", "00\\$ab$12${a} ", NULL};
    int test_start[] = {7,              1,
                        3,              4,              5, 9,  9};
    int test_end[] =   {11,             5,
                        7,              8,              7, 11, 12};
    int start;
    int end;
    char *name;

    for (int i = 0; exp[i]; i++) {
        mx_find_param(exp[i], &start, &end, &name);
        printf("%d) %s\t%d\t%d\n", i + 1, exp[i], start, end);
        assert(start == test_start[i]);
        assert(end == test_end[i]);
        free(name);
    }

    printf("\nSUCCESS\n----\n");
    system("leaks -q ush");
    return 0;
}
