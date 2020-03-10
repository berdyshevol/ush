#ifndef LISTSTR_H
#define LISTSTR_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// --------------------------- list of structs of key, value
typedef struct list_str {
    char *key;
    char *value;
    struct list_str *next;
} t_liststr;

t_liststr *mx_liststr_init(char *key, char *value);
void mx_liststr_push_front(t_liststr **head, char *key, char *value);
void mx_liststr_push_back(t_liststr **head, char *key, char *value);
void mx_liststr_pop_front(t_liststr **head);
int mx_liststr_length(t_liststr *head);
void mx_convert_strlist_strvector(t_liststr *arguments,
                                  char ***argv, int *argc);
void mx_delete_strvector(char ***argv, int *argc);
void mx_liststr_delete_node(t_liststr *node);
void mx_liststr_delete(t_liststr **head);
//----------------------------------
#endif
