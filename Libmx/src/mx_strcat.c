//int mx_strlen(const char *s);
#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int i = mx_strlen(s1);
    int j = 0;
    if (s2)
        while ((s1[i] = s2[j]) != '\0') {
            i++;
            j++;
        }
    return s1;
    /*solution from GNU C Library (glibc) https://github.com/bminor/glibc/blob/master/string/strcat.c
    strcpy (s1 + strlen (s1), s2);
    return s1;
    */
}

