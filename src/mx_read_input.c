#include "ush.h"

static void check_realloc(t_global_environment *g) {
    if (g->cursor >= g->bufsize) {
        g->bufsize += 128;
        g->str = realloc(g->str, g->bufsize);
        mx_check_malloc(g->str);
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
    g->show_his = g->his_point + 1;
    if (g->his_point < 499)
        g->his_point++;
    else {
        mx_strdel(&g->history[0]);
        for (int i = 0; i < 500; i++)
            g->history[i] = g->history[i + 1];
        mx_strdel(&g->history[499]);
    }
}

static void finish_reading(t_global_environment *g) {
    g->str[g->cursor] = '\0';
    mx_strdel(&g->tmp_str);
    g->full_tmp_str = false;
    add_history(g);
}

void mx_read_input(t_global_environment *g) {
    bool add_cursor = false;

    g->str = mx_strnew(g->bufsize);
    mx_check_malloc(g->str);
    for (g->cursor = 0;; g->cursor++) {
        if (g->backcpase_his == true) {
            g->cursor--;
            g->backcpase_his = false;
        }
        read(0, &g->buff, sizeof(&g->buff));
//        read(0, &g->buff, 1); // for debug in clion
        if (!mx_history(g))
            add_cursor = mx_ckeck_buffer(g);
        if (g->str[g->cursor] == '\n')
            break;
        check_realloc(g);
        g->cursor = (!add_cursor) ? g->cursor - 1 : g->cursor;
        memset(g->buff, '\0', 5);
    }
    finish_reading(g);
}

