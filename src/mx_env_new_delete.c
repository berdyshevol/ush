#include "environment.h"

t_environment *mx_env_new(void) {
    return NULL;
}

void mx_env_delete(t_environment **env) {
    mx_liststr_delete(env);
}
