#include "ush.h"

static void sig_int() {
    exit(130);
}

static void signals() {
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
}

void mx_init_shell(t_global_environment *gv) {
    //if (gv->shellName != NULL) free(gv->shellName);
    gv->shellName = "brothers' shell"; // TODO: удалить
    // do somthing
    signals();
    // настройка сигналов
}
