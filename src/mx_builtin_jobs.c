#include "ush.h"

int mx_jobs(t_global_environment *gv) {
    t_stoped *head = gv->jobs_list;

    if(gv->cnf->agvsize == 1) {
        while (head->next != NULL) {
            if(head->str != NULL)
                printf("[%d] suspended %s\n", head->n, head->str);
            head = head->next;   
        }
        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "jobs: sorry not in this version\n");
        return EXIT_FAILURE;
    }
}
