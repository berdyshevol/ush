//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

char **av;
int avsize;
char *infile;
char *outfile;
char *errfile;

void avreserve (int n) {
    int oldavsize = avsize;

    if (avsize > n + 1)
        return;

    avsize = 2 * (oldavsize + 1);
    av = realloc (av, avsize * sizeof (*av));
    while (oldavsize < avsize)
        av[oldavsize++] = NULL;
}
/**
 * can parse only:
 * <
 * >
 * 2>
 * @param line
 */
void parseline (char *line) {
    char *a;
    int n;

    infile = outfile = errfile = NULL;
    for (n = 0; n < avsize; n++)
        av[n] = NULL;

    a = strtok (line, " \t\r\n");
    for (n = 0; a; n++) {
        if (a[0] == '<')
            infile = a[1] ? a + 1 : strtok (NULL, " \t\r\n");
        else if (a[0] == '>')
            outfile = a[1] ? a + 1 : strtok (NULL, " \t\r\n");
        else if (a[0] == '2' && a[1] == '>')
            errfile = a[2] ? a + 2 : strtok (NULL, " \t\r\n");
        else {
            avreserve (n);
            av[n] = a;
        }
        a = strtok (NULL, " \t\r\n");
    }
}

void doexec (void) {
    int fd;
    // process redirections
    if (infile) {
        if ((fd = open (infile, O_RDONLY)) < 0) {
            perror (infile);
            exit (1);
        }
        if (fd != 0) {
            dup2 (fd, 0);
            close (fd);
        }
    }

    if (outfile) {
        if ((fd = open (outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
            perror (outfile);
            exit (1);
        }
        if (fd != 1) {
            dup2 (fd, 1);
            close (fd);
        }
    }

    if (errfile) {
        if ((fd = open (errfile, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
            perror (outfile);
            exit (1);
        }
        if (fd != 2) {
            dup2 (fd, 2);
            close (fd);
        }
    }
    // process bin file
    execvp (av[0], av);
    perror (av[0]);
    exit (1);
}

void mx_eval(t_global_environment *gv, char *line) {
    int pid;

    gv->a = 1; // TODO: delete. This is for compiler
    avsize = 0;
    parseline(line);
    if (av[0] == NULL)
        return;
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
