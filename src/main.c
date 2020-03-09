#include "ush.h"

int main() {
    t_global_environment *gv = NULL;

    mx_init_shell(&gv);
    mx_driver_loop(gv);
    mx_free_all(gv);
    return 0;
}
