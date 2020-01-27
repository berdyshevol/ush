#include "ush.h"

// ----------- EXPORT builtin function -----------

static int name_compare(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2) && *s2 != '=') {
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 == '=')
        return 0;
    return *s1 - *s2;
}

void mx_builtin_export(t_config *cnf) {
    extern char **environ;

    if (cnf->agv[1])
        for (int i = 1; cnf->agv[i] != NULL; i++)
            putenv(cnf->agv[i]);
    else {
        mx_sort_arr(environ, mx_cmp_name);
        for (int i = 0; environ[i] != NULL; i++) {
            if (name_compare("_", environ[i]) == 0)
                continue;
            else {
                mx_printstr(environ[i]);
                mx_printchar('\n');
            }
        }
    }
}

// ----------- UNSET builtin function -----------

void mx_builtin_unset(t_config *cnf) {
    unsetenv(cnf->agv[1]);
}

// ----------- FG builtin function ----------- Not done

void mx_builtin_fg(t_config *cnf) {
    mx_printstr("fg: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

// ----------- EXIT builtin function -----------

void mx_builtin_exit(t_config *cnf) {
    if (cnf->agv[1] == NULL)
        exit(0);
    else
        exit(mx_atoi(cnf->agv[1]));
}

// ----------- ENV builtin function ----------- Not done

void mx_builtin_env(t_config *cnf) {
    mx_printstr("env: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

// ----------- CD builtin function -----------

static char *home_finding(char *var) {
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        if (name_compare(var, environ[i]) == 0)
            return mx_memchr(environ[i], '/', mx_strlen(environ[i]));
    }
    return NULL;
} 

void mx_builtin_cd(t_config *cnf) {
    if (cnf->agv[1] == NULL) {
        if (chdir(home_finding("HOME")) != 0)
            perror("cd");
    }
    else if (chdir(cnf->agv[1]) != 0)
        perror("cd");
}

// ----------- PWD builtin function -----------

void mx_builtin_pwd() {
    char PathName[PATH_MAX];

    mx_printstr(getwd(PathName));
    mx_printstr("\n");
}

void mx_builtin_which(t_config *cnf) {
    mx_printstr("which: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_builtin_echo(t_config *cnf) {
    mx_printstr("echo: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

void mx_alias(t_config *cnf) {
    mx_printstr("alias: ");
    mx_printstr(cnf->gv->shellName);
    mx_printstr("\n");
}

