#include "ush.h"

static void signal_ctr_c() {
    printf("\nCTR + C\nExit.\n");
    mx_reset_input_mode();
    exit(130);
}

static void signal_ctr_d() {
    printf("\nCTR + D\nExit.\n");
    mx_reset_input_mode();
    exit(0);
}

static void backspace(t_global_environment *g) {
    if (g->cursor == 0)
        printf("\ru$h> ");
    else if (g->cursor == 1) {
        g->str[g->cursor] = '\0';
        printf("\ru$h> %s", g->str);
        write(1, " \b", strlen(" \b"));
        g->cursor = 0;
    }
    else if (g->cursor > 1) {
        g->str[g->cursor - 1] = '\0';
        printf("\ru$h> %s", g->str);
        write(1, "\b \b", strlen("\b \b"));
        g->cursor =  g->cursor - 2;
    }
}

void mx_ckeck_buffer(t_global_environment *g) {
    int len = strlen(g->buff);

    if (len == 1 && g->buff[0] == 3)
        signal_ctr_c();
    else if (len == 1 && g->buff[0] == 4)
        signal_ctr_d();
    else if (len == 1 && (g->buff[0] > 8 && g->buff[0] < 127)) {
        write(1, &g->buff[0], 1);
        g->str[g->cursor] = g->buff[0];
    }
    else if (len == 1 && g->buff[0] == 127)
        backspace(g);   
}
