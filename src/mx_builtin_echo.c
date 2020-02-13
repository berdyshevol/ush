#include "ush.h"

static char *replace_escapes(char *str) {
    char *replace = mx_replace_substr(str, "\x0a", "\\n");
    char *result = mx_strnew(ARG_MAX);

    strcpy(result, replace);
    mx_strdel(&replace);
    replace = mx_replace_substr(result, "\x09", "\\t");
    strcpy(result, replace);
    mx_strdel(&replace);
    replace = mx_replace_substr(result, "\x0b", "\\v");
    strcpy(result, replace);
    mx_strdel(&replace);
    replace = mx_replace_substr(result, "\x07", "\\a");
    strcpy(result, replace);
    mx_strdel(&replace);
    replace = mx_replace_substr(result, "\x09", "\\t");
    strcpy(result, replace);
    mx_strdel(&replace);
    return result;
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

static void print_newline(bool minus_n) {
    if (minus_n)
        printf("\x1b[0;47;30m%%\x1b[0m\n");
    else
        printf("\n");
}

int mx_builtin_echo(t_global_environment *gv) {
    int flags[3] = {0};
    unsigned int index = 0;
    char *output = NULL;

    index = init_flags(gv->cnf->agv, flags);
    while (gv->cnf->agv[index]) {
        if (flags[minus_E])
            output = replace_escapes(gv->cnf->agv[index]);
        else
            output = strdup(gv->cnf->agv[index]);
        printf("%s", output);
        mx_strdel(&output);
        index++;
        if (gv->cnf->agv[index])
            printf(" ");
    }
    print_newline(flags[minus_n]);
    return EXIT_SUCCESS;
}
