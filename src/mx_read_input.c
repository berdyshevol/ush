#include "ush.h"

static void check_malloc(char *str);

void mx_read_input(t_global_environment *g) {
    unsigned int bufsize = 128;
    bool add_cursor = false;

    g->str = mx_strnew(bufsize);
    check_malloc(g->str);
   for (g->cursor = 0;; g->cursor++) {
        read(0, &g->buff, 4);
        add_cursor = mx_ckeck_buffer(g);
        if (!mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n')
            write(1, ">", 1);
        else if (mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n') {
            g->str[g->cursor] = '\0';
            return;
        }
        if (g->cursor >= bufsize) {
            bufsize += 128; //If we have exceeded the str, reallocate.
            g->str = realloc(g->str, bufsize);
            check_malloc(g->str);
        }
        g->cursor = (!add_cursor) ? g->cursor - 1 : g->cursor;
        memset(g->buff, '\0', 5);
    }
}

static void check_malloc(char *str) {
    if (!str) {
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}
