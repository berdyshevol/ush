//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

static void check_malloc(char *buffer);

char *mx_read_input(void) {
    int bufsize = 128;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    check_malloc(buffer);
    for (int position = 0;; position++) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else
            buffer[position] = c;
        if (position >= bufsize) {
            bufsize += 128; //If we have exceeded the buffer, reallocate.
            buffer = realloc(buffer, bufsize);
            check_malloc(buffer);
        }
    }
}

static void check_malloc(char *buffer) {
    if (!buffer) {
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}
