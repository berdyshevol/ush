//
// Created by Oleg Berdyshev on 3/7/20.
//

#include "ush.h"

void mx_print_oddnumberofquotes() {
    mx_printerr("Odd number of quotes.\n");
}

void mx_print_error_nearnewline() {
    mx_printstr("parse error near `\\n'\n");
}

void mx_print_nocmd(char *cmd) {
    mx_printerr("ush: ");
    if (strlen(cmd) < 257) {
        mx_printerr("command not found: ");
        mx_printerr(cmd);
        mx_printerr("\n");
    }
    else {
        mx_printerr("file name too long: ");
        mx_printerr(cmd);
        mx_printerr("\n");
    }
    exit(127);
}
