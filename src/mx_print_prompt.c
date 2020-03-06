#include "ush.h"

void mx_print_prompt(void) {
    char *prompt_msg = "\x1b[1K\r\x1b[2Ku$h> ";
    mx_printstr(prompt_msg);
}

void mx_check_malloc(char *str) {
    if (!str) { // Use in mx_read_input.c
        fprintf(stderr, "ush: allocation error\n");
        exit(1);
    }
}
