#include "ush.h"

void mx_print_prompt(void) {
    char *prompt_msg = "\x1b[1K\r\x1b[2Ku$h> ";
    mx_printstr(prompt_msg);
}
