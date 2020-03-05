//
// Created by Oleg Berdyshev on 3/5/20.
//

#include "parser.h"

bool mx_find_file_expansion(char *exp, int *start, int *end, char **name) {
    *start = 0;
    *end = 0;
    *name = NULL;
    e_mode mode = unquote;
    char *find_begin = NULL;

    for (unsigned long i = 0; i < strlen(exp); i++) {
        mx_change_mode(&mode, exp, i);
        if (exp[i] == '~' && mode == unquote) {
            // check if this is the beginning of the word
            if (i == 0 || mx_is_whitespace(exp[i - 1])) {
                // check if this is ~-
                if (i != strlen(exp) && exp[i + 1] == '-') {
                    *start = i;
                    *end = i + 1;
                    *name = strdup("~-");
                    return true;
                }
                // check if this is ~+
                else if (i != strlen(exp) && exp[i + 1] == '+') {
                        *start = i;
                        *end = i + 1;
                        *name = strdup("~+");
                        return true;
                }
                //this is mere ~
                else {
                    *start = i;
                    *end = i;
                    *name = strdup("~");
                    return true;
                }
            }
        }
    }
    return false;
}

////test mx_find_param
//#include <assert.h>
//int main(void) {
//    char *exp[] =      {"echo ~",   "echo ~+",  "echo ~-",
//                        "echo '~'", "echo' ~+'", "echo' ~-'",
//                        "echo 1~",   "echo 1~+",  "echo 1~-", NULL};
//    int test_start[] = {5,           5,         5,
//                        0,           0,         0,
//                        0,           0,         0,};
//    int test_end[] =   {5,          6,          6,
//                        0,          0,          0,
//                        0,           0,         0,};
//    char *test_name[]={ "~",     "~+",           "~-",
//                        NULL,       NULL,       NULL,
//                        NULL,       NULL,       NULL};
//    int start;
//    int end;
//    char *name;
//
//    for (int i = 0; exp[i]; i++) {
//        mx_find_file_expansion(exp[i], &start, &end, &name);
//        printf("%d) %s\t%d\t%d\t%s\n", i + 1, exp[i], start, end, name);
//        assert(start == test_start[i]);
//        assert(end == test_end[i]);
//        if (name != NULL)
//            assert(strcmp(name, test_name[i]) == 0);
//        else
//            assert(name == test_name[i]);
//        free(name);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}
