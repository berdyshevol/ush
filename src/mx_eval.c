//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

char **av;
int avsize;

void avreserve (int n) {
    int oldavsize = avsize;

    if (avsize > n + 1)
        return;

    avsize = 2 * (oldavsize + 1);
    av = realloc (av, avsize * sizeof (*av));
    while (oldavsize < avsize)
        av[oldavsize++] = NULL;
}

void parseline (char *line) {
    char *a;
    int n;

    for (n = 0; n < avsize; n++)
        av[n] = NULL;

    a = strtok (line, " \t\r\n");
    for (n = 0; a; n++) {
        avreserve (n);
        av[n] = a;
        a = strtok (NULL, " \t\r\n");
    }
}

void doexec (void) {
    execvp (av[0], av);
    perror (av[0]);
    exit (1);
}

void mx_eval(t_global_environment *gv, char *line) {
    int pid;

    gv->a = 1; // TODO: delete. This is for compiler
    avsize = 0;
    parseline(line);
//    if (av[0] == NULL)
//        return;
    switch (pid = fork ()) {
        case -1:
            mx_printerr("fork");
            break;
        case 0:
            doexec();
            break;
        default:
            waitpid(pid, NULL, 0);
            break;
    }
}
