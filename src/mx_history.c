#include "ush.h"

static void up_arrow(t_global_environment *g) {
    int leng = strlen(g->str);
    
    for(int i = 0; i < leng; i++)
        printf("\b\x1b[0K");
    mx_strdel(&g->str);
    g->str = strdup(g->history[g->show_his]);
    printf("\ru$h> %s", g->str);
    g->cursor = strlen(g->str);
}

static bool down_arrow(t_global_environment *g) {
    int leng = strlen(g->str);
    
    for(int i = 0; i < leng; i++)
        printf("\b\x1b[0K");
    mx_strdel(&g->str);
    g->str = strdup(g->history[g->show_his]);
    printf("\ru$h> %s", g->str);
    g->cursor = strlen(g->str);
    return true;
}

static bool show_tmp_str(t_global_environment *g) {
    int leng = strlen(g->str);

    for(int i = 0; i < leng; i++)
        printf("\b\x1b[0K");
    mx_strdel(&g->str);
    g->str = strdup(g->tmp_str);
    printf("\ru$h> %s", g->str);
    g->cursor = strlen(g->str);
    mx_strdel(&g->tmp_str);
    g->full_tmp_str = false;
    return true;
}

static bool go_up_arrow(t_global_environment *g) {
    if (strcmp(g->buff, MX_UP_AR) == 0) {
        if (g->full_tmp_str == false) {
            mx_strdel(&g->tmp_str);
            g->tmp_str = strdup(g->str);
            g->full_tmp_str = true;
        }
        if (g->show_his > 0)
            g->show_his--;
        if (g->history[g->show_his] != NULL) {
            up_arrow(g);
            return true;
        }
        g->backcpase_his = true;
    }
    return false;
}

int mx_history(t_global_environment *g) {
    if (go_up_arrow(g))
        return true;
    if (strcmp(g->buff, MX_DOWN_AR) == 0) {
        if (g->full_tmp_str == false) {
            mx_strdel(&g->tmp_str);
            g->tmp_str = strdup(g->str);
            g->full_tmp_str = true;
        }
        if (g->show_his < 500 && g->history[g->show_his] != NULL)
            g->show_his++;
        if (g->history[g->show_his] != NULL)
            return down_arrow(g);
        else 
            return show_tmp_str(g);
        g->backcpase_his = true;
    }
    return false;
}
