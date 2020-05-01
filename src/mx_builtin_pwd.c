#include "ush.h"

static int flags_while(char **argv, int i, int *physical) {
    for (int j = 1; argv[i][j]; j++) {
        if (argv[i][j] == 'P')
            *physical = 1;
        else if (argv[i][j] != 'L' && (argv[i][j] != '-'
                                       || (argv[i][j] == '-' && j == 2))) {
            fprintf(stderr, "pwd: bad option: -%c\n", argv[i][j]);
            return -1;
        }
    }
    return 0;
}

static int get_flags(char **argv) {
    bool stoper = 0;
    int physical = 0;

    for (int i = 1; argv[i] != NULL; i++) {
        if (argv[i][0] == '-' && !stoper) {
            if ((argv[i][1] == '-' && argv[i][2] == '\0')
                || argv[i][1] == '\0')
                stoper = 1;
            if (flags_while(argv, i, &physical) == -1)
                return -1;
        }
        else {
            fprintf(stderr, "pwd: too many arguments\n");
            return -1;
        }
    }
    return physical;
}

void mx_pwd_check(t_global_environment *gv) {
    char link_read[PATH_MAX + 1];
    char *where_we = getwd(NULL);

    if (realpath(getenv("PWD"), link_read) == NULL 
        || strcmp(realpath(getenv("PWD"), link_read), where_we) != 0) {
            gv->pwd = mx_strdup(where_we);
            gv->oldpwd = mx_strdup(where_we);
            setenv("PWD", where_we, 1);
            setenv("OLDPWD", where_we, 1);
        }
    else {
        gv->pwd = mx_strdup(getenv("PWD"));
        gv->oldpwd = mx_strdup(getenv("OLDPWD"));
    }
    mx_strdel(&where_we);
}

int mx_builtin_pwd(t_global_environment *gv) {
    int physical;

    if ((physical = get_flags(gv->cnf->agv)) != -1) {
        if (physical) {
            char *path = getwd(NULL);
            
            puts(path);
            mx_strdel(&path);
        }
        else
            puts(gv->pwd);
    } else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
