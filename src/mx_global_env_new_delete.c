#include "ush.h"

t_stoped *mx_add_empty_job(t_global_environment *g) {
    t_stoped *job = malloc(sizeof(t_stoped));

    job->n = g->list_index;
    job->str = NULL;
    job->pid = 0;
    job->next = NULL;
    g->list_index++;
    return job;
}

static void jobs_list(t_global_environment *g, t_stoped **list) {
    t_stoped *head = mx_add_empty_job(g);
    t_stoped *cur = mx_add_empty_job(g);
    t_stoped *tmp = mx_add_empty_job(g);
    t_stoped *tmp1 = mx_add_empty_job(g);
    t_stoped *tmp2 = mx_add_empty_job(g);
    t_stoped *tmp3 = mx_add_empty_job(g);
    t_stoped *tmp4 = mx_add_empty_job(g);
    t_stoped *tmp5 = mx_add_empty_job(g);
    t_stoped *tmp6 = mx_add_empty_job(g);

    *list = head;
    head->next = cur;
    cur->next = tmp;
    tmp->next = tmp1;
    tmp1->next = tmp2;
    tmp2->next = tmp3;
    tmp3->next = tmp4;
    tmp4->next = tmp5;
    tmp5->next = tmp6;
}

void initialize_variables_ivan(t_global_environment *gv) {
    gv->his_point = 0;            // History add index
    gv->show_his = 0;             // History show index
    gv->bufsize = 128;            // Size str for realloc
    gv->full_tmp_str = false;     // History flag
    gv->backcpase_his = false;    // History flag
    for (int i = 0; i < 500; i++)
        gv->history[i] = NULL;    // History NULL array
    gv->tmp_str = mx_strnew(128); // Temporary str for history
    gv->list_index = 1;           // Jobs index
    jobs_list(gv, &gv->jobs_list);// Stoped process list
    gv->last_stoped = NULL;       // Last stoped process
    gv->count_jobs = 0;           // Jobs counter
    gv->ctr_d = false;            // Safety latch for Ctr + D
}

t_global_environment *mx_new_global_env(void) {
    t_global_environment *gv = malloc(sizeof(t_global_environment));
    
    gv->shellName = "brothers' shell"; // DELETE
    
    gv->prompt = "\x1b[1K\r\x1b[2Ku$h> ";
    gv->vars = mx_env_new();
    mx_env_set_var("?", "0", &(gv->vars));
    gv->functions = mx_env_new();
    gv->alias = mx_env_new();
    gv->cnf = NULL;
    gv->pwd = mx_strdup(getenv("PWD"));
    gv->oldpwd = mx_strdup(getenv("OLDPWD"));
    initialize_variables_ivan(gv);
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
    mx_strdel(&((*gv)->pwd));
    mx_strdel(&((*gv)->oldpwd));
    free(*gv);
    *gv = NULL;
}
