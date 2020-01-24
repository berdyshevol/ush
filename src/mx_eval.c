//
// Created by Oleg Berdyshev on 1/22/20.
//

#include "ush.h"

char **av;
int avsize;
char *infile;
char *outfile;
char *errfile;
char *outcmd;

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
 * can do only one operetion:
 * either can parse:
 *     <
 *     >
 *     2>
 * or can do pipe:
 *     |
 * @param line
 */
void parseline (char *line) {
    char *a;
    int n;

    outcmd = infile = outfile = errfile = NULL;
    for (n = 0; n < avsize; n++)
        av[n] = NULL;

    a = strtok (line, " \t\r\n");
    for (n = 0; a; n++) {
        if (a[0] == '<')
            infile = a[1] ? a + 1 : strtok (NULL, " \t\r\n");
        else if (a[0] == '>')
            outfile = a[1] ? a + 1 : strtok (NULL, " \t\r\n");
        else if (a[0] == '|') {
            if (!a[1])
                outcmd = strtok (NULL, "");
            else {
                outcmd = a + 1;
                a = strtok (NULL, "");
                while (a > outcmd && !a[-1])
                    *--a = ' ';
            }
        }
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
    int pipefds[2];
    // do pipeline
    while (outcmd) {
        if (outfile) {
            fprintf (stderr, "syntax error: > in pipe writer\n");
            exit (1);
        }

        if (pipe (pipefds) < 0) {
            perror ("pipe");
            exit (0);
        }

        switch (fork ()) {

            case -1:
                perror ("fork");
                exit (1);

            case 0: // child (left)
                if (pipefds[1] != 1) {
                    dup2 (pipefds[1], 1);
                    close (pipefds[1]);
                }
                close (pipefds[0]);
                outcmd = NULL;
                break;

            default: // parent (right)
                if (pipefds[0] != 0) {
                    dup2 (pipefds[0], 0);
                    close (pipefds[0]);
                }
                close (pipefds[1]);
                parseline (outcmd);
                if (infile) {
                    fprintf (stderr, "syntax error: < in pipe reader\n");
                    exit (1);
                }
                break;
        }
    }
    // do redirections
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
            perror (errfile);
            exit (1);
        }
        if (fd != 2) {
            dup2 (fd, 2);
            close (fd);
        }
    }
    // exec bin
    execvp (av[0], av);
    perror (av[0]);
    exit (1);
}

int try_builtin(t_global_environment *gv, char *cmd) {
    int i = 0;
	t_pair_cmd_name getBuiltIns[] = {
		{"export", mx_builtin_export},
		{"unset", mx_builtin_unset},
		{"exit", mx_builtin_exit},
		{"env", mx_builtin_env},
		{"cd", mx_builtin_cd},
		{"pwd", mx_builtin_pwd},
		{"which", mx_builtin_which},
        {"echo", mx_builtin_echo},
        {"alias", mx_alias},
		{NULL, NULL}
	};

    while (getBuiltIns[i].command)
	{
		if (_strcmp(build->args[0], getBuiltIns[i].command) == 0)
		{
			getBuiltIns[i].func(build);
			freeArgsAndBuffer(build);
			return (true);
		}
		i++;
	}
	return (false);


}

void mx_eval(t_global_environment *gv, char *line) {
    int pid;

    // TODO: delete. This is for compiler
    avsize = 0;
    parseline(line);
    if (!try_builtin(gv, av[0])) {
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
}
