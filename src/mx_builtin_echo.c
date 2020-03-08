#include "ush.h"

static char *replace_escapes(char *str) {
    char *tmp = mx_strdup(str);

    mx_get_str_spase("\\n", '\n', &tmp);
    mx_get_str_spase("\\t", '\t', &tmp);
    mx_get_str_spase("\\v", '\v', &tmp);
    mx_get_str_spase("\\r", '\r', &tmp);
    mx_get_str_spase("\\b", '\b', &tmp);
    mx_get_str_spase("\\a", '\a', &tmp);
    mx_get_str_spase("\\cmd_subs", '\f', &tmp);
    mx_get_str_spase("\\e", '\033', &tmp);
    mx_get_str_spase("\\t", '\t', &tmp);
    mx_more_escapes(&tmp);
    return tmp;
}

static int check_flags(char *src, char *regex) {
    regex_t reg;
    int result;

    regcomp(&reg, regex, REG_EXTENDED);
    result = regexec(&reg, src, 0, NULL, 0);
    regfree(&reg);
    return result == 0;
}

static unsigned int init_flags(char **arg, int *flags) {
    unsigned int index = 1;

    while (arg[index]) {
        if (check_flags(arg[index], "^-[nEe]+$")) {
            for (unsigned int i = 0; i < strlen(arg[index]); i++) {
                if (arg[index][i] == 'E')
                    flags[minus_E] = true;
                if (arg[index][i] == 'e')
                    flags[minus_E] = false;
                if (arg[index][i] == 'n')
                    flags[minus_n] = true;
            }
        }
        else
            break;
        index++;
    }
    return index;
}

static void print_newline(bool no_new_line, bool only_sound) {
    if (no_new_line) {
        if (only_sound)
            return;
        else
            printf("\x1b[0;47;30m%%\x1b[0m\n");
    }
    else
        printf("\n");
}

int mx_builtin_echo(t_global_environment *gv) {
    int flags[5] = {0};
    unsigned int index = 0;
    char *output = NULL;
    
    index = init_flags(gv->cnf->agv, flags);
    while (gv->cnf->agv[index]) {
        if (flags[minus_E])
            mx_printstr(gv->cnf->agv[index]);
        else {
            output = replace_escapes(gv->cnf->agv[index]);
            flags[4] = mx_check_sound(output);
            mx_printstr(output);
            mx_strdel(&output);
        }
        index++;
        if (gv->cnf->agv[index])
            printf(" ");
    }
    print_newline(flags[minus_n], flags[4]);
    return EXIT_SUCCESS;
}

