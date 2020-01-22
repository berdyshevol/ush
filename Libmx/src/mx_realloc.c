#include "libmx.h"

static int my_min(int a, int b);

void *mx_realloc(void *ptr, size_t size) {
    int sz;
    void *p;

    if (ptr == NULL && size != 0)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        ptr = NULL;
        return malloc(malloc_size(0));
    }
    sz = my_min(size, malloc_size(ptr));
    p = malloc(size);
    if (p == NULL)
        return NULL;
    mx_memmove(p, ptr, sz);
    free(ptr);
    ptr = NULL;
    return p;
}

static int my_min(int a, int b) {
    return a < b ? a : b;
}

