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

static int open_or_not_catalog(char *dir, bool old) {
    char link_read[PATH_MAX + 1];
    struct stat sb;

    lstat(dir, &sb);
    if (old) {
        if (mx_strcmp(dir, realpath(dir, link_read)) != 0) {
            fprintf(stderr, "cd: not a directory: %s\n", dir);
            return EXIT_FAILURE;
        }
    }
    else if (MX_ISLNK(sb.st_mode)) {
        fprintf(stderr, "cd: not a directory: %s\n", dir);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int open_incoming_catalog(t_global_environment *gv,
                                 char *dir, bool old) {
    if (chdir(dir) != 0) {
        perror("cd");
        return EXIT_FAILURE;
    }
    else {
        mx_strdel(&gv->oldpwd);
        gv->oldpwd = mx_strdup(gv->pwd);
        setenv("OLDPWD", gv->pwd, 1);
        mx_strdel(&gv->pwd);
        gv->pwd = mx_strdup(dir);
        setenv("PWD", gv->pwd, 1);
    }
    if (old) {
        if (strstr(dir, getenv("HOME")))
            puts(mx_replace_substr(dir, getenv("HOME"), "~"));
        else
            puts(dir);
    }
    return EXIT_SUCCESS;
}

void mx_flags_settings_cd(t_global_environment *gv, bool *flags,
                           int *status, char *dir) {
    if (flags[CD_s]) {
        if (open_or_not_catalog(dir, flags[CD_minus]) == EXIT_SUCCESS)
            *status = open_incoming_catalog(gv, dir, flags[CD_minus]);
        else
            *status = EXIT_FAILURE;
    }
    else if (flags[CD_P]) {
        char link_read[PATH_MAX];

        *status = open_incoming_catalog(gv, realpath(dir, link_read),
                                        flags[CD_minus]);
    }
    else
        *status = open_incoming_catalog(gv, dir, flags[CD_minus]);
}
