//
// Created by Oleg Berdyshev on 2/7/20.
//

#include "liststr.h"

int mx_liststr_length(t_liststr *head) {
    int count = 0;
    if (head != NULL) {
        for (t_liststr *cur = head; cur != NULL; cur = cur->next)
            count++;
    }
    return count;
}

//#include <assert.h>
//int main(void) {
//    t_liststr *l = NULL;
//    printf("test 1\n");
//    assert(mx_liststr_length(l) == 0);
//    mx_liststr_push_back(&l, NULL, NULL);
//    printf("test 2\n");
//    assert(mx_liststr_length(l) == 1);
//    mx_liststr_push_front(&l, NULL, NULL);
//    printf("test 3\n");
//    assert(mx_liststr_length(l) == 2);
//    mx_liststr_pop_front(&l);
//    printf("test 4\n");
//    assert(mx_liststr_length(l) == 1);
//    mx_liststr_delete(&l);
//    printf("test 5\n");
//    assert(mx_liststr_length(l) == 0);
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
