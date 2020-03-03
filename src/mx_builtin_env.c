//
// Created by Pavlo Symonov on 2/21/20.
//

// ----------- ENV builtin function ----------- Not done

#include "ush.h"

char *mx_get_env_name(char *var) {
    if (var != NULL)
        return strndup(var, mx_get_char_index(var, '='));
    return NULL;
}

char *mx_get_env_value(char *var) {
    if (var != NULL)
        return strdup(var + mx_get_char_index(var, '=') + 1);
    return NULL;
}

static void clearenv() {
    extern char **environ;
    char **vars_to_del = NULL;
    char *delname = NULL;

    if (environ[0] != NULL) {
        vars_to_del = mx_environ_copy();
        for (int i = 0; vars_to_del[i]; i++) {
            delname = mx_get_env_name(vars_to_del[i]);
            unsetenv(delname);
            mx_strdel(&delname);
        }
        mx_del_strarr(&vars_to_del);
    }
}

int mx_print_error_env(char ch, int err, char *str) {
    if (err == 0) {
        fprintf(stderr, "env: unsetenv %s: Invalid argument\n", str);
    }
    else {
        if (err == 1)
            fprintf(stderr, "env: option requires an argument -- %c\n", ch);
        else if (err == 2)
            fprintf(stderr, "env: bad option: -- %c\n", ch);
        fprintf(stderr, "usage: env [-i] [-P utilpath] [-u name]\n");
        fprintf(stderr, "[name=value ...] [utility [argument ...]]\n");
    }
    return EXIT_FAILURE;
}

static char *get_flag_arg(char **arr, int *ch_index, int *status, int *i) {
    if (arr[0][(*ch_index) + 1] == '\0') {
        if (arr[1] == NULL) {
            *status = mx_print_error_env(arr[0][*ch_index], 1, NULL);
        }
        else {
            *ch_index = -1;
            (*i)++;
            return mx_strdup(arr[1]);
        }
    }
    else {
        int step = *ch_index + 1;

        *ch_index = -1;
        return mx_strdup(arr[0] + step);
    }
    return NULL;
}

static void check_delname(char *name, int *status) {
    if (!(*status))
        if ((*status = mx_match_search(name, "=")))
            mx_print_error_env(0, 0, name);
}

static void delete_name(char **name) {
    unsetenv(*name);
    mx_strdel(name);
}

static int flags_finding(char **arr,  char **path, int *i) {
    int status = 0;

    for (int j = 0; arr[0][j]; j++) {
        if (arr[0][j] == 'P') {
            mx_strdel(path);
            *path = get_flag_arg(arr, &j, &status, i);
        }
        else if (arr[0][j] == 'u') {
            char *delname = get_flag_arg(arr, &j, &status, i);

            check_delname(delname, &status);
            delete_name(&delname);
        }
        else if (arr[0][j] != 'i' && arr[0][j] != '-')
            return mx_print_error_env(arr[0][j], 2, NULL);
        if (status || j == -1)
            break;
    }
    return status;
}

static int flags_handler_env(char **argv, int *i, char **path) {
    int res = 0;

    for (*i = 1; argv[*i] != NULL && !res; (*i)++) {
        if (argv[*i][0] == '-' && strcmp(argv[*i], "--") != 0) {
            if (mx_match_search(argv[*i], MX_ENV_I))
                clearenv();
            res = flags_finding(&argv[*i], path, i);
        }
        else {
            if (strcmp(argv[*i], "--") == 0)
                (*i)--;
            break;
        }
    }
    return res;
}

static void vars_handler_env(char **arr, int *i) {
    char *p = NULL;

    for (; arr[*i] && (p = strchr(arr[*i], '=')); (*i)++) {
        *p = '\0';
        setenv(arr[*i], p + 1, 1);
        *p = '=';
    }
}

static bool dir_or_not(char *path) {
    DIR* dir = opendir(path);

    if (!dir)
        return false;
    closedir(dir);
    return true;
}

static char *file_name_finding(char *path, char *name) {
    char cancat[PATH_MAX];
    char *file_name = NULL;

    if (path != NULL) {
        sprintf(cancat, "%s/%s", path, name);
        file_name = mx_strdup(cancat);
    }
    else
        file_name = mx_strdup(name);
    return file_name;
}

static void process_errors_env(char **arr) {
    int res = 0;

    if (dir_or_not(*arr)) {
        fprintf(stderr, "env: %s: %s\n", strerror(errno), *arr);
        res = 126;
    }
    else if (errno == ENOENT) {
        fprintf(stderr, "env: %s: %s\n", *arr, strerror(errno));
        res = 127;
    }
    else
        res = 1;
    _exit(res);
}

static void inside_the_process(char **arr, char *name, char *path) {
    int res = 0;

    if (path) {
        if (strchr(*arr, '/'))
            res = execv(*arr,  arr);
        else
            res = execv(name,  arr);
    }
    else
        res = execvp(name, arr);
    printf("Pasha");
    if (res == -1)
        process_errors_env(arr);
}

static int exec_env_file(char **arr, char *path) {
    char *file_name = file_name_finding(path, *arr);
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        perror("fork");
    else if (pid == 0) {
        inside_the_process(arr, file_name, path);
    }
    else {
        wait(&status);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
    }
    mx_strdel(&file_name);
    return status;
}

static void print_env() {
    extern char **environ;

    mx_print_strarr(environ, "\n");
}

void mx_putenv(char *var) {
    static char name[1024];
    static char val[1024];
    char *received_name = mx_get_env_name(var);
    char *received_val = mx_get_env_value(var);

    sprintf(name, "%s", received_name);
    sprintf(val, "%s", received_val);
    setenv(name, val, 1);
    mx_strdel(&received_name);
    mx_strdel(&received_val);
}

static void env_fill(char **src) {
    clearenv();
    for (int i = 0; src[i]; i++)
        mx_putenv(src[i]);
}

int mx_builtin_env(t_global_environment *gv) {
    int status = 0;
    int i;
    char *path = NULL;
    char **env_copy = mx_environ_copy();

    if (!(status = flags_handler_env(gv->cnf->agv, &i, &path))) {
        vars_handler_env(gv->cnf->agv, &i);
        if (gv->cnf->agv[i] == NULL)
            print_env();
        else {
            status = exec_env_file(&gv->cnf->agv[i], path);
        }
    }
    env_fill(env_copy);
    mx_del_strarr(&env_copy);
    mx_strdel(&path);
    return status;
}
