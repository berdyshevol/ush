#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;
    char *res,                                // the return string
        *ins = (char *)str,                   // the next insert point
            *temp = (char *)str,              // str rewrite
                *entry = mx_strstr(str, sub); // changing variable
    if (entry == NULL)
        return temp;
    int strLen = mx_strlen(str), subLen = mx_strlen(sub),
        repLen = mx_strlen(replace), count, distLen;

    // count the number of replacements needed
    for (count = 0; (entry = mx_strstr(ins, sub)); ++count)
        ins = entry + subLen;
    // allocate memory for new string
    entry = res = mx_strnew(strLen + (repLen - subLen) * count);
    if (res == NULL)
        return NULL;

    // entry points to the end of the res string
    // ins points to the occurrence of sub in str
    // temp points to the remainder of str after "end of sub"
    while (count--) {
        ins = mx_strstr(temp, sub);
        distLen = ins - temp;
        entry = mx_strncpy(entry, temp, distLen) + distLen;
        entry = mx_strcpy(entry, replace) + repLen;
        temp += distLen + subLen;
    }
    mx_strcpy(entry, temp);
    return res;
}
