#include "ush.h"

static bool is_number_fg(char *str) {
    if (str[0] != '%')
        return false;
    for(int i = 1; str[i] != '\0'; i++)
        if (str[i] < 48 || str[i] > 57)
            return false;
    return true;
}

static void launch_by_pid(t_global_environment *g, int *status, int num) {
    t_stoped *head = g->jobs_list;
    char *str = mx_itoa(num);

    while ((head->next != NULL) && (head->n != num))
        head = head->next;
    if (head->n == num && head->pid != 0)
        mx_continue_process(status, head, g);
    else {
        fprintf(stderr, "fg: %%%s: no such job\n", str);
        mx_env_set_var("?", "1", &(g->vars));
    }
    mx_strdel(&str);
}

static bool check_str(char *src, char *str) {
    bool res;
    char *s1 = NULL;
    char *s2 = NULL;
    char *s3 = NULL;

    if (src == NULL || src[0] == '\0')
        return false;
    s1 = mx_first_word(src);
    s2 = mx_first_word(str);
    if (strlen(s2) < strlen(s1)) {
        s3 = strndup(s1, strlen(s2));
        res = (strcmp(s3, s2) == 0);
        mx_strdel(&s3);
    }
    else
        res = (strcmp(s1, s2) == 0);
    mx_strdel(&s2);
    mx_strdel(&s1);
    return res;
}

static void launch_by_command(t_global_environment *g, int *st, char *str) { // доделать тут сегментит
    t_stoped *head = g->jobs_list;
    int i = (str[0] == '%') ? 1 : 0;

    while (head->next != NULL && !check_str(head->str, &str[i]))
        head = head->next;
    if (check_str(head->str, &str[i]))
        mx_continue_process(st, head, g);
    else {
        fprintf(stderr, "fg: job not found: %s\n", str);
        mx_env_set_var("?", "1", &(g->vars));
    }
}

int mx_builtin_fg(t_global_environment *gv) {
    int status = 0;

    if (gv->count_jobs || gv->cnf->agvsize > 1) {
        if(gv->cnf->agvsize == 1)
            mx_continue_process(&status, gv->last_stoped, gv);
        else if (gv->cnf->agvsize > 1)
            for (int i = 1; i < gv->cnf->agvsize; i++) {
                if (is_number_fg(gv->cnf->agv[i])) 
                    launch_by_pid(gv, &status, atoi(&gv->cnf->agv[i][1]));
                else
                    launch_by_command(gv, &status, gv->cnf->agv[i]);
            }
        gv->ctr_d = false;
    }
    else {
        mx_printerr("fg: no current job\n");
        status = 1;
    }
    return status;
}
