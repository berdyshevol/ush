#include "ush.h"

static void up_arrow(t_global_environment *g) {
    int leng = strlen(g->str);
    
    mx_strdel(&g->str);
    for(int i = 0; i < leng; i++)
        printf("\b\x1b[0K");
    g->str = strdup(g->history[g->show_his]);
    printf("\ru$h> %s", g->str);
    g->cursor = strlen(g->str);
    if (g->show_his > 0)
        g->show_his--;
}

static void down_arrow(t_global_environment *g) {
    int leng = strlen(g->str);
    
    mx_strdel(&g->str);
    for(int i = 0; i < leng; i++)
        printf("\b\x1b[0K");
    g->str = strdup(g->history[g->show_his]);
    printf("\ru$h> %s", g->str);
    g->cursor = strlen(g->str);
    if (g->show_his < 500 && g->history[g->show_his + 1] != NULL)
        g->show_his++;
}

int mx_history(t_global_environment *g) {
    if (strcmp(g->buff, MX_UP_AR) == 0) {
        if (g->history[g->show_his] != NULL) {
            up_arrow(g);
            return true;
        }
        g->backcpase_his = true;
    }
    if (strcmp(g->buff, MX_DOWN_AR) == 0) {
        if (g->history[g->show_his] != NULL) {
            down_arrow(g);
            return true;
        }
        g->backcpase_his = true;
    }
    return false;
}
