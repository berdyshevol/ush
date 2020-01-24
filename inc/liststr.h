#include <stdlib.h>

// --------------------------- list
typedef struct list_str {
    char *key;
    char *value;
    struct list_str *next;
} t_liststr;

// api functions
t_liststr *mx_liststr_init(char *key, char *value);
void mx_liststr_push_front(t_liststr **head, char *key, char *value);
void mx_liststr_pop_front(t_liststr **head);
void mx_liststr_delete(t_liststr **head);
//----------------------------------

