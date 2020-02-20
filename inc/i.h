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

typedef enum {
    minus_e,
    minus_E,
    minus_n,
} e_echo;

struct termios stored_settings;

void mx_read_input(t_global_environment *g);
bool mx_ckeck_buffer(t_global_environment *g);
void mx_reset_input_mode(void);
int mx_history(t_global_environment *g);

#endif
