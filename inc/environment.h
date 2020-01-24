#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "liststr.h"
#include <string.h>  // TODO: may be replace from libmx

// ---------------------------- data
// typedef struct environment {
//     t_liststr *bindings;
// } t_environment;

typedef t_liststr t_environment;

// --------------------------- api
t_environment *mx_env_init(void);
char *mx_env_get_value(char *key, t_environment *env);
void mx_env_set_var(char *key, char *value, t_environment **env);
void mx_env_delete(t_environment **env);

#endif
