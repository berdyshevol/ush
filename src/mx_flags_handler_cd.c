#include "ush.h"

static int flags_cd_handle(char ch, bool **is_flag) {
    if (ch == 's')
        (*is_flag)[CD_s] = true;
    else if (ch == 'P')
        (*is_flag)[CD_P] = true;
    else {
        fprintf(stderr, "u$h: cd: -%c: invalid option\n", ch);
        fprintf(stderr, "cd: usage: cd [-s|-P] [dir]\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

char *mx_flags_handler_cd(char **argv, bool **is_flag,
                              t_global_environment *gv) {
    for (int i = 1; argv[i] != NULL; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-' && argv[i][2] == '\0')
                return argv[i + 1] == NULL ? mx_strdup(getenv("HOME"))
                                           : mx_strdup(argv[i + 1]);
            else if (argv[i][1] == '\0') {
                (*is_flag)[CD_minus] = true;
                return mx_strdup(gv->oldpwd);
            }
            else
                for (int j = 1; argv[i][j]; j++)
                    if (flags_cd_handle(argv[i][j], is_flag))
                        return NULL;
        }
        else
            return mx_strdup(argv[i]);
    }
    return mx_strdup(getenv("HOME"));
}
