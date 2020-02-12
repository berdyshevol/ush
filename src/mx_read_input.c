#include "ush.h"

static void check_malloc(char *str);
// static void history(t_global_environment *g);
// static void add_history(t_global_environment *g);

void mx_read_input(t_global_environment *g) {
    unsigned int bufsize = 128;
    bool add_cursor = false;

    g->str = mx_strnew(bufsize);
    check_malloc(g->str);
    for (g->cursor = 0;; g->cursor++) {
        read(0, &g->buff, 4);
        //history(g);
        add_cursor = mx_ckeck_buffer(g);
        if (!mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n')
            write(1, ">", 1);
        else if (mx_is_closed_expression(g->str) && g->str[g->cursor] == '\n') {
            g->str[g->cursor] = '\0';
            // add_history(g);
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

// static void add_history(t_global_environment *g) {
//     if (g->his_point != 0) {
//         if (strcmp(g->str, g->history[g->his_point - 1]) != 0) {
//             g->history[g->his_point] = strdup(g->str);
//             g->his_point++;
//         }
//     }
//     else {
//         g->history[g->his_point] = strdup(g->str);
//         g->his_point++;
//     }
//     g->show_his = g->his_point - 1;
// }

// static void history(t_global_environment *g) {
//     if (strcmp(g->buff, MX_UP_ARROW) == 0) {
//         g->show_his = (g->show_his >= 0) ? g->show_his-- : 500;
//         printf("\ru$h> %s", g->history[g->show_his]);
//         mx_strdel(&g->str);
//         g->str = strdup(g->history[g->show_his]);
//     }
//     else if (strcmp(g->buff, MX_DOWN_ARROW) == 0) {
//         g->show_his = (g->show_his < 500) ? g->show_his++ : 0;
//         if (g->show_his < g->his_point) {
//             printf("\ru$h> %s", g->history[g->show_his]);
//             mx_strdel(&g->str);
//             g->str = strdup(g->history[g->show_his]);
//         }
//         else 
//             printf("\ru$h> ");
//     }
// }

static void check_malloc(char *str) {
    if (!str) {
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}
