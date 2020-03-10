#ifndef USH_I_H
#define USH_I_H

#include <term.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

#include "ush.h"

#define MX_UP_AR "\x1b\x5b\x41"
#define MX_DOWN_AR "\x1b\x5b\x42"
#define MX_RIGHT_AR "\x1b\x5b\x43"
#define MX_LEFT_AR "\x1b\x5b\x44"
#define MX_MOVE_CURSOR_LEFT "\033[1C"
#define MX_MOVE_CURSOR_RIGHT "\033[1D"

#define MX_W_INT(w) (*(int *) & (w))
#define MX_WSTOPSIG(w) (MX_W_INT(w) >> 8)
#define MX_WSTATUS(w) (MX_W_INT(w) & 0177)
#define MX_WIFSTOPPED(w) (MX_WSTATUS(w) == _WSTOPPED && MX_WSTOPSIG(w) != 0x13)
#define MX_WEXITSTATUS(w) ((MX_W_INT(w) >> 8) & 0x000000ff)

#define MX_WST(w)           (_W_INT(w) & 0177)
#define MX_WIFEXIT(w)       (MX_WST(w) == 0)
// #define MX_WIFSIG(x)        (MX_WST(x) != _WSTOPPED && MX_WST(x) != 0)
// #define MX_WTERMSIG(x)      (MX_WST(x))
// #define MX_EXSTATUS(x)      ((MX_W_INT(x) >> 8) & 0x000000ff)

typedef enum {
    minus_e,
    minus_E,
    minus_n,
} e_echo;

struct termios stored_settings;
struct termios new_settings;

void mx_read_input(t_global_environment *g);
bool mx_ckeck_buffer(t_global_environment *g);
void mx_reset_input_mode(void);
int mx_history(t_global_environment *g);
void mx_set_input_mode (void);
void mx_set_default_signals();
t_stoped *mx_add_empty_job(t_global_environment *g);
void mx_set_default_signals(void);
void mx_continue_process(int *st, t_stoped *ps, t_global_environment *g);

#endif
