//
// Created by Oleg Berdyshev on 2/7/20.
//
#include "liststr.h"

/**
 * returns null terminated array of stings
 * @param arguments
 * @param argv
 * @param argc
 */
void mx_convert_strlist_strvector(t_liststr *arguments,
                                  char ***argv, int *argc) {
    t_liststr *cur = arguments;
    *argc = mx_liststr_length(arguments);

    char **strvector = malloc((*argc) * sizeof (char *) + 1);
    for (int i = 0; i < (*argc); i++, cur = cur->next) {
        strvector[i] = strdup(cur->key);
    }
    strvector[*argc] = NULL;
    *argv = strvector;
}

void mx_delete_strvector(char ***argv, int *argc) {
    if (argv == NULL || *argv == NULL)
        return ;
    for (int i = 0; i < *argc; i++) {
        if ((*argv)[i] != NULL)
            free((*argv)[i]);
    }
    free(*argv);
    *argv = NULL;
    *argc = 0;
}

//#include <assert.h>
//int main(void) {
//    t_liststr *l = NULL;
//    char *testvec1[] = {NULL};
//    int testcount1 = 0;
//    char **res1 = NULL;
//    int count;
//    mx_convert_strlist_strvector(l, &res1, &count);
//    assert(count == testcount1);
//    assert(testvec1[0] == res1[0]);
//    printf("test 1\n");
//
//    char *testvec2[] = {"hello", NULL};
//    int testcount2 = 1;
//    char **res2 = NULL;
//    int count2;
//    l = mx_liststr_init("hello", NULL);
//    mx_convert_strlist_strvector(l, &res2, &count2);
//    assert(count2 == testcount2);
//    assert(strcmp(testvec2[0], res2[0]) == 0);
//    assert(testvec2[1] == res2[1]);
//    printf("test 2\n");
//
//    char *testvec3[] = {"hello", "world", NULL};
//    int testcount3 = 2;
//    char **res3 = NULL;
//    int count3;
//    mx_liststr_push_back(&l, "world", NULL);
//    mx_convert_strlist_strvector(l, &res3, &count3);
//    assert(count3 == testcount3);
//    assert(strcmp(testvec3[0], res3[0]) == 0);
//    assert(strcmp(testvec3[1], res3[1]) == 0);
//    assert(NULL == res3[2]);
//    printf("test 3\n");
//
//    mx_delete_strvector(&res3, &count3);
//    assert(count3 == 0);
//    assert(res3 == NULL);
//    printf("test 4\n");
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//
//    return 0;
//}
