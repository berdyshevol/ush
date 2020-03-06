#include "ush.h"

static void free_jobs_list(t_global_environment *gv) {
    t_stoped *head = gv->jobs_list;
    t_stoped *next;

    while (head->next != NULL) {
        mx_strdel(&head->str);
        next = head->next;
        free(head);
        head = next;
    }
    if (head->str != NULL)
        mx_strdel(&head->str);
    free(head);
}

void mx_free_all(t_global_environment *gv) {
    free_jobs_list(gv);
    free(gv);
}
