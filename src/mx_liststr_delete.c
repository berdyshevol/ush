#include "liststr.h"

void mx_liststr_delete(t_liststr **head) {
    while (*head != NULL)
        mx_liststr_pop_front(head);
}
