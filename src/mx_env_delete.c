#include "environment.h"

void mx_env_delete(t_environment **env) {
    mx_liststr_delete(env);
}
