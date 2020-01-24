#include "environment.h"

static t_environment *mx_env_lookup_key(char *key, t_environment *env);

void mx_env_set_var(char *key, char *value, t_environment **env) {
    t_environment *res = mx_env_lookup_key(key, *env);
    if (res != NULL) {
        char *tmp = res->value;
        res->value = _strdup(value);  // TODO: make sure to change _strdup
        free(tmp);
    }
    else
        mx_liststr_push_front(env, _strdup(key), _strdup(value)); // TODO: make sure to change _strdup
}

static t_environment *mx_env_lookup_key(char *key, t_environment *env) {
    for (t_environment *cur = env; cur != NULL; cur = cur->next) {
        if (strcmp(cur->key, key) == 0)
            return cur;
    }
    return NULL;
}
