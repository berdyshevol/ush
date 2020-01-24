#include "environment.h"

char *mx_env_get_value(char *key, t_environment *env) {
    for (t_environment *cur = env; cur != NULL; cur = cur->next) {
        if (strcmp(cur->key, key) == 0)
            return cur->value;  // TODO: mauby send in heap: _strdup(cur->value)
    }
    return NULL;
}
