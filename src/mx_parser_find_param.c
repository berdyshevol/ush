//
// Created by Oleg Berdyshev on 2/19/20.
//

#include "parser.h"

bool mx_find_param(char *exp, int *start, int *end, char **name) {
    *start = 0;
    *name = NULL;
    e_mode mode = unquote;
    char *find_begin = NULL;

    for (int i = 0; i < strlen(exp); i++) {
        //char *find_begin = strstr(&exp[i], "$");
        mx_change_mode(&mode, exp, i);
        if (exp[i] == '$' && mode != quote) {
            find_begin = &exp[i];
            //if (find_begin) {
                if (mx_count_esc(exp, find_begin - exp) % 2 != 0)
                    continue;
                if (find_begin[1] == '{') {
                    *start = find_begin - exp;
                    char *find_end = mx_strstr_esc(find_begin, "}");
                    if (find_end == NULL)
                        *end = strlen(exp) - 1;
                    else {
                        *end = find_end - exp;
                        *name = strndup(exp + *start + 2, *end - *start - 2);
                        return true;
                    }
                } else {
                    *start = find_begin - exp;
                    int i = 1;
                    char *temp = strndup(find_begin + 1, i);
                    while (mx_is_valid_parname(temp) && find_begin[i]) {
                        free(temp);
                        i++;
                        temp = strndup(find_begin + 1, i);
                    }
                    free(temp);
                    if (*start != find_begin - exp + i - 1) {
                        *end = find_begin - exp + i - 1;
                        char *p = exp + *start + 1;
                        int n = *end - *start;
                        *name = strndup(exp + *start + 1, *end - *start);
                        return true;
                    }

                }
            //}
        }
    }
    *end = 0;
    return false;
}

////test mx_find_param
//#include <assert.h>
//int main(void) {
//    char *exp[] =      {"'$name'$name", "\"$name\"'$name",
//                        "012$_a67-80", "0123${12}000", "0\\$ab$ab-",
//                        "01\\$ab$12$ab-", "00\\$ab$12${a} ", NULL};
//    int test_start[] = {7,              1,
//                        3,              4,              5, 9,  9};
//    int test_end[] =   {11,             5,
//                        7,              8,              7, 11, 12};
//    int start;
//    int end;
//    char *name;
//
//    for (int i = 0; exp[i]; i++) {
//        mx_find_param(exp[i], &start, &end, &name);
//        printf("%d) %s\t%d\t%d\n", i + 1, exp[i], start, end);
//        assert(start == test_start[i]);
//        assert(end == test_end[i]);
//        free(name);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
