//
// Created by Oleg Berdyshev on 2/7/20.
//

#include "libmx.h"
#include <string.h>

static bool is_empty(char *s);

// ----    API Function
char *mx_strjoin_with_space(char *s1, char *s2) {
    if (is_empty(s1) && is_empty(s2))
        return NULL;
    else if (is_empty(s1)){
        return strdup(s2);
    }
    else if (is_empty(s2)) {
        return strdup(s1);
    }
    char *s = mx_strjoin(s1, " ");
    char *res = mx_strjoin(s, s2);
    free(s);
    return res;
}

// ----- Static Functions
static bool is_empty(char *s) {
    if (s == NULL)
        return true;
    if (s[0] == '\0')
        return true;
    return false;
}

//#include <assert.h>
//int main(void) {
//    char *s1[] = {"hello",          NULL,    "hello", NULL};
//    char *s2[] = {"world",          "world", NULL,    NULL};
//    char *test[] = {"hello world",  "world", "hello", NULL};
//    for (int i = 0; i < 4; i++) {
//        char *res = mx_strjoin_with_space(s1[i], s2[i]);
//        if (res != NULL)
//            assert(strcmp(test[i], res) == 0);
//        else
//            assert(test[i] == res);
//        printf("test %d\n", i+1);
//        free(res);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
