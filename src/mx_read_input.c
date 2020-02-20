#include "ush.h"

static void check_malloc(char *str) {
    if (!str) {
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}

static void check_realloc(t_global_environment *g) {
    if (g->cursor >= g->bufsize) {
        g->bufsize += 128; //If we have exceeded the str, reallocate.
        g->str = realloc(g->str, g->bufsize);
        check_malloc(g->str);
    }
}

static void add_history(t_global_environment *g) {
    if (g->his_point == 0) {
        mx_strdel(&g->history[g->his_point]);
        g->history[g->his_point] = strdup(g->str);
    }
    else if (strcmp(g->str, g->history[g->his_point - 1]) != 0) {
        mx_strdel(&g->history[g->his_point]);
        g->history[g->his_point] = strdup(g->str);
    }
    else
        return;
    g->show_his = g->his_point;
    g->his_point++;
    if (g->his_point > 500)
        g->his_point = 0;
}

void mx_read_input(t_global_environment *g) {
    bool add_cursor = false;

    g->str = mx_strnew(g->bufsize);
    check_malloc(g->str);
    for (g->cursor = 0;; g->cursor++) {
        if (g->backcpase_his == true) {
            g->cursor--;
            g->backcpase_his = false;
        }
        read(0, &g->buff, 4);
        if (!mx_history(g))
            add_cursor = mx_ckeck_buffer(g);
        if (!mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n')
            write(1, ">", 1);
        else if (mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n') {
            g->str[g->cursor] = '\0';
            add_history(g);
            return;
        }
        check_realloc(g);
        g->cursor = (!add_cursor) ? g->cursor - 1 : g->cursor;
        memset(g->buff, '\0', 5);
    }
}
