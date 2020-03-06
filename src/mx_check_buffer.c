#include "ush.h"

static void signal_ctr_c(t_global_environment *g) {
    mx_strdel(&g->str);
    g->str = mx_strnew(128);
    g->cursor = 0;
    g->backcpase_his = true;
    printf("\n\r\x1b[2Ku$h> ");
    mx_env_set_var("?", "130", &(g->vars));
}

static void signal_ctr_d(t_global_environment *g) {
    if (g->count_jobs && !g->ctr_d) {
        mx_printerr("\nu$h: you have suspended jobs.");
        g->ctr_d = true;
        signal_ctr_c(g);
        mx_env_set_var("?", "146", &(g->vars));
        return;
    }
    if (g->ctr_d || !g->count_jobs) {
        printf("\n\n\r\x1b[2K[Process completed]\n\n");
        mx_reset_input_mode();
        exit(0);
    }
}

static void backspace(t_global_environment *g) {
    if (g->cursor == 0) {
        printf("\r\x1b[2Ku$h> ");
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
        signal_ctr_d(g);
    else if (strcmp(g->buff, MX_RIGHT_AR) == 0)
        g->backcpase_his = true;
    else if (strcmp(g->buff, MX_LEFT_AR) == 0)
        g->backcpase_his = true;
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
