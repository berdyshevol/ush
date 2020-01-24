#include "liststr.h"

void mx_liststr_pop_front(t_liststr **head) {
    if (head == NULL) return;
    if (*head == NULL) return;

    t_liststr *tList = *head;
    *head = (*head)->next;
    free(tList);
}
