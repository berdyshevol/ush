#include "ush.h"

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

static void set_pwd_oldpwd(t_global_environment *gv, char *dir) {
    mx_strdel(&gv->oldpwd);
    gv->oldpwd = mx_strdup(gv->pwd);
    setenv("OLDPWD", gv->pwd, 1);
    mx_strdel(&gv->pwd);
    gv->pwd = mx_strdup(dir);
    setenv("PWD", gv->pwd, 1);
}

static int open_incoming_catalog(t_global_environment *gv,
                                 char *dir, bool old, char *inc_dir) {
    if (chdir(dir) != 0) {
        fprintf(stderr, "cd: %s: %s\n", strerror(errno), inc_dir);
        return EXIT_FAILURE;
    }
    else
        set_pwd_oldpwd(gv, dir);
    if (old) {
        if (strstr(dir, getenv("HOME"))) {
            char *tilda = mx_replace_substr(dir, getenv("HOME"), "~");
            
            puts(tilda);
            mx_strdel(&tilda);
        }
        else
            puts(dir);
    }
    return EXIT_SUCCESS;
}

int mx_flags_settings_cd(t_global_environment *gv, bool *flags,
                           char *inc_dir, char *dir) {
    int status = 0;

    if (flags[CD_s]) {
        if (open_or_not_catalog(dir, flags[CD_minus]) == EXIT_SUCCESS)
            status = open_incoming_catalog(gv, dir, flags[CD_minus], inc_dir);
        else
            status = EXIT_FAILURE;
    }
    else if (flags[CD_P]) {
        char link_read[PATH_MAX];

        status = open_incoming_catalog(gv, realpath(dir, link_read),
                                        flags[CD_minus], inc_dir);
    }
    else
        status = open_incoming_catalog(gv, dir, flags[CD_minus], inc_dir);
    return status;
}
