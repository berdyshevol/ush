#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "liststr.h"

typedef t_liststr t_environment;

// --------------------------- api
t_environment *mx_env_new(void);
char *mx_env_get_value(char *key, t_environment *env);
void mx_env_set_var(char *key, char *value, t_environment **env);
void mx_env_delete(t_environment **env);

#endif
