#include "ush.h"

static void signal_ctr_c(t_global_environment *g) {
    printf("\nHISTORY:\n");
    for (int i = 0; g->history[i] != NULL; i++)
        printf("#%i -> \"%s\"\n", i, g->history[i]);
    mx_print_prompt();
}

static void signal_ctr_d() {
    printf("\nCTR + D\nExit.\n");
    mx_reset_input_mode();
    exit(0);
}

static void backspace(t_global_environment *g) {
    if (g->cursor == 0) {
        printf("\ru$h> ");
        memset(g->str, '\0', strlen(g->str));
    }
    else if (g->cursor == 1) {
        printf("\b\x1b[0K");
        memset(g->str, '\0', (strlen(g->str) - 1));
        g->cursor--;
    }
    else if (g->cursor > 1) {
        printf("\b\x1b[0K");
        g->str[g->cursor - 1] = '\0';
        g->cursor =  g->cursor - 1;
    }
}

bool mx_ckeck_buffer(t_global_environment *g) {
    int len = strlen(g->buff);

    if (len == 1 && g->buff[0] == 3)
        signal_ctr_c(g);
    else if (len == 1 && g->buff[0] == 4)
        signal_ctr_d();
    else if (len == 1 && (g->buff[0] >= 0 && g->buff[0] < 127)) {
        write(1, &g->buff[0], 1);
        g->str[g->cursor] = g->buff[0];
    }
    else if (g->buff[0] == 127) {
        backspace(g);   
        return false;
    }
    return true;
}
