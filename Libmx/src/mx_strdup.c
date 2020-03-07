#include "libmx.h"

char *mx_strdup(const char *str) {
    int len = mx_strlen(str);
    char *result;
    char *dup = mx_strnew(len);
    if (len > 0)
        result = mx_strcpy(dup, str);
    return result;
}

