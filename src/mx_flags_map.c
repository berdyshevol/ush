#include "ush.h"

bool *mx_flags_map(int flags_num) {
    bool *res = (bool *) malloc(sizeof (bool) * flags_num);

    for (int i = 0; i < flags_num; i++)
        res[i] = false;
    return res;
}
