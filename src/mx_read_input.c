#include "ush.h"

static void check_malloc(char *str);

char *mx_read_input(void) {
    int bufsize = 128;
    char *str = malloc(sizeof(char) * bufsize);

    check_malloc(str);
    for (int i = 0;; i++) {
        read(0, &str[i], 1);
        if (!mx_is_closed_expression(str) && (str[i] == EOF || str[i] == '\n'))
            write(1, ">", 1);
        else if (mx_is_closed_expression(str)
            && (str[i] == EOF || str[i] == '\n')) {
            str[i] = '\0';
            return str;
        }
        if (i >= bufsize) {
            bufsize += 128; //If we have exceeded the str, reallocate.
            str = realloc(str, bufsize);
            check_malloc(str);
        }
    }
}

static void check_malloc(char *str) {
    if (!str) {
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}
