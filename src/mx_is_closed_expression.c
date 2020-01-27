#include "ush.h"

static int _which_closing_char(char c);
static int _which_opening_char(char c);

int mx_is_closed_expression(char *s) {
    int id;
    int flag = 1; // 1 - закрытое выражение, 0 - открытое
    int index = -1;

    for (int i = 0; s[i]; i++) {
        if (flag == 1) {
            id = _which_opening_char(s[i]);
            if (id > -1) {
                flag = 0;
                index = id;
            }
        }
        else if (flag == 0) {
            id = _which_closing_char(s[i]);
            if (id > -1 && id == index) {
                flag = 1;
                index = -1;
            }
        }
    }
    if (flag == 1)
        return 1;
    else
        return 0;
}

static int _which_closing_char(char c) {
    char *opening_chars = "'\")}";
    int len = strlen(opening_chars);

    for (int i = 0; i < len; i++)
        if (c == opening_chars[i])
            return i;
    return -1;
}

static int _which_opening_char(char c) {
    char *opening_chars = "'\"({";
    int len = strlen(opening_chars);

    for (int i = 0; i < len; i++)
        if (c == opening_chars[i])
            return i;
    return -1;
}
