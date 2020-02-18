//
// Created by Pavlo Symonov on 2/15/20.
//

#include "ush.h"

static int flags_finding(char *str, bool **is_flag, int i) {
    if (str[1] == '-' && str[2] == '\0')
        return i + 1;
    else {
        for (int j = 1; str[j]; j++) {
            if (str[j] == 'a')
                (*is_flag)[WH_a] = true;
            else if (str[j] == 's')
                (*is_flag)[WH_s] = true;
            else {
                fprintf(stderr, "which: bad option: -%c\n", str[j]);
                return -1;
            }
        }
    }
    return 0;
}

static int flags_handler_which(char **argv, bool **is_flag) {
    int stoper = 0;
    int res = 0;

    for (int i = 1; argv[i] != NULL; i++) {
        if (argv[i][0] == '-' && !stoper) {
            if ((res = flags_finding(argv[i], is_flag, i)) == -1
                || res == i + 1)
                break;
        }
        else {
            res = i;
            break;
        }
    }
    return res;
}

static void access_finding(char *str, char *tok,
                            bool *flags, int *flag) {
    while (tok) {
        int len = strlen(tok) + 2 + strlen(str);
        char *file = malloc(len);

        sprintf(file, "%s/%s", tok, str);
        if (access(file, MX_OK) == 0) {
            if (!(flags[WH_s])) {
                puts(file);
                *flag = 1;
                if (!(flags[WH_a])) {
                    free(file);
                    break;
                }
            }
            *flag = 1;
        }
        tok = strtok(NULL, ":");
        free(file);
    }
}

static int which_checking(t_global_environment *gv, bool *flags, int index) {
    int flag = 0;
    int status = EXIT_SUCCESS;

    for (int i = index; gv->cnf->agv[i] != NULL; i++) {
        char *path = strdup(getenv("PATH"));
        char *tok = strtok(path, ":");

        access_finding(gv->cnf->agv[i], tok, flags, &flag);
        if(!flag) {
            if (!(flags[WH_s])) {
                fprintf(stderr, "%s not found\n", gv->cnf->agv[i]);
            }
            status = EXIT_FAILURE;
        }
        free(path);
        flag = 0;
    }
    return status;
}

int mx_builtin_which(t_global_environment *gv) {
    bool *flags = flags_map(2);
    int status = 0;
    int index = 0;

    if ((index = flags_handler_which(gv->cnf->agv, &flags)) < 1) {
        free(flags);
        system("leaks -q ush");
        return EXIT_FAILURE;
    }
    status = which_checking(gv, flags, index);
    free(flags);
    system("leaks -q ush");
    return status;
}
