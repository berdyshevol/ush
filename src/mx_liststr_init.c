#include "liststr.h"

t_liststr *mx_liststr_init(char *key, char *value) {
    t_liststr *p = malloc(sizeof(t_liststr));
    
    if (p == NULL) return NULL;
    p->key = key;
    p->value = value;
    p->next = NULL;
    return p;
}
