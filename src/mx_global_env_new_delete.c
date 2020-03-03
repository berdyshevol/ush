//
// Created by Oleg Berdyshev on 1/22/20.
//
#include "ush.h"

// t_stoped *mx_add_empty_job(t_global_environment *g) {
//     t_stoped *job = malloc(sizeof(t_stoped));
//     job->n = g->list_index;
//     job->str = NULL;
//     job->next = NULL;
//     g->list_index++;
//     return job;
// }
// static t_stoped *list(t_global_environment *g) {
//     t_stoped *head = g->jobs_list;
//     for(; g->list_index <= 5; head = head->next)
//         head->next = mx_add_empty_job(g);
// }

t_global_environment *mx_new_global_env(void) {
    t_global_environment *gv = malloc(sizeof(t_global_environment));
    gv->shellName = "brothers' shell"; // delete
    gv->prompt = "u$h> ";
    gv->vars = mx_env_new();
    mx_env_set_var("?", "0", &(gv->vars));
    gv->functions = mx_env_new();
    gv->alias = mx_env_new();
    gv->cnf = NULL;
    gv->pwd = mx_strdup(getenv("PWD"));
    gv->oldpwd = mx_strdup(getenv("OLDPWD"));
    gv->his_point = 0; // History add index
    gv->show_his = 0;  // History show index
    gv->bufsize = 128; // Size str for realloc
    gv->full_tmp_str = false;  // History flag
    gv->backcpase_his = false; // History flag
    for (int i = 0; i < 500; i++)
        gv->history[i] = NULL; // History NULL array
    gv->tmp_str = NULL; // Str for history
    gv->list_index = 1; // Jobs index
    // gv->jobs_list = list(gv); // Stoped process list
    gv->last_stoped = NULL; // Last stoped process
    return gv;
}

void mx_delete_global_env(t_global_environment **gv) {
    if (gv == NULL)
        return ;
    if (*gv == NULL)
        return ;
    mx_env_delete(&((*gv)->vars));
    mx_env_delete(&((*gv)->functions));
    mx_env_delete(&((*gv)->alias));
//    if ((*gv)->cnf != NULL)
//        mx_delete_config(&((*gv)->cnf));
    free(*gv);
    *gv = NULL;
}
