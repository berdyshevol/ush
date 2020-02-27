//
// Created by Oleg Berdyshev on 1/29/20.
//

#include "ush.h"
#include "evaluator.h"

// epansions
void mx_alias_expansion(t_exp *exp, t_global_environment *gv) {

}

// -----------------------------------
e_exp_type mx_parse(t_exp exp) {
    return mx_get_expressiontype_by_id(mx_get_binary_opid(exp));
}
// -----------------------------------

/* not used
 *
t_exp mx_cadr(t_exp exp) {
    char *op = mx_get_name_by_id(mx_get_op_id(exp));
    char *car = mx_car(exp, op);
    return car;

}

t_exp mx_caddr(t_exp exp) {
    return exp;
}

t_exp mx_cadddr(t_exp exp) {
    //  TODO: но правильней всего взять элемент после ||
    return exp;
}

// Begin packages a sequence of expressions into a single expression.
// TODO: что это (define (begin? exp) (tagged-list? exp 'begin))

t_exp mx_begin_actions(t_exp exp) {
    char *op = mx_get_name_by_id(mx_get_op_id(exp));
    t_exp car = mx_left_exp(exp, op);
    return car;
}
*/

bool mx_is_last_exp(t_exp seq, char *op_name) {
    //char *op_name = mx_get_op_name(seq);
    char *cdr = mx_right_exp(seq, op_name);
    bool return_value = cdr == NULL;
    free(cdr);
    return return_value;
}

t_exp mx_first_exp(t_exp seq, char *op_name) {
    //char *op_name = mx_get_op_name(seq);
    char *car = mx_left_exp(seq, op_name);
    return car;
}

t_exp mx_rest_exps(t_exp seq, char *op_name) {
    //char *op_name = mx_get_op_name(seq);
    char *cdr = mx_right_exp(seq, op_name);
    return cdr;
}

// A procedure application is simple-command
// TODO: что это? (define (application? exp) (pair? exp))

t_exp mx_command(t_exp exp) {
    //return mx_left_exp(exp);
    //char *car = mx_left_exp(exp, " ");
    //return car;
    t_exp first_word = mx_first_word(exp);
    return first_word;
}

bool mx_is_no_operands(t_exp ops) {
    return ops == NULL;
}

t_exp mx_operands(t_exp exp) {
//    char *cdr = mx_right_exp(exp, " ");
//    return cdr;
    //t_exp rest_words = mx_rest_words(exp);
    t_exp operands = strdup(exp); // операторы включают в себя название команды
    return operands;
}

t_exp mx_first_operand(t_exp ops) {
    char *car = mx_left_exp(ops, " ");
    return car;
}

t_exp mx_rest_operands(t_exp ops) {
    char *cdr = mx_right_exp(ops, " ");
    return cdr;
}

// words
// self_evaluating
t_eval_result mx_self_evaluating (t_exp exp, t_global_environment *env) {
    t_eval_result result = mx_new_evalresult();
    result->text = strdup(exp);
    return result;
}
// text of quotation
t_eval_result mx_text_of_quotation(t_exp exp, t_global_environment *gv) {
    t_eval_result result = mx_new_evalresult();
    result->text = mx_extract_unary_operand(exp);
    return result;
}

//t_eval_result mx_eval_doublequote(t_exp exp, t_global_environment *gv) {
//    char *seq = mx_extract_unary_operand(exp);
//    char * delim = " ";
//    t_eval_result result = mx_eval_sequence_ofwords(seq, delim, gv);   //
//    // TODO eval string not sequence_ofwords!!!!!!
//    free(seq);
//    return result;
//}

// Expansions
t_eval_result mx_lookup_variable_value(t_exp exp, t_global_environment *gv) {
    t_eval_result result = mx_new_evalresult();
    char *name = mx_extract_unary_operand(exp);
    char *env_var_value = NULL;
    char *local_var_value = NULL;
    char *value = NULL;

    env_var_value = getenv(name);
    if (env_var_value == NULL) {
        local_var_value = mx_env_get_value(name, gv->vars);
        if (local_var_value != NULL)
            value = local_var_value;
    }
    else
        value = strdup(env_var_value);

    result->text = value;

    mx_strdel(&name);
    return result;
}

t_eval_result mx_file_extension(t_exp exp, t_global_environment *gv) {
    char *operand = mx_extract_unary_operand(exp);
    t_eval_result result = mx_new_evalresult();
    char *home = getenv("HOME");
    char *fullpath = mx_strjoin(home, operand);
    result->text = fullpath;
    mx_strdel(&operand);
    return result;
}

t_eval_result  mx_eval_command_substitution(t_exp exp, t_global_environment *gv) {
    char *seq = mx_extract_unary_operand(exp);
    // TODO: где-то здесь нужно запусть новый процесс и отловить его результат
    t_eval_result result = mx_eval(seq, gv, NULL, NULL);
    mx_strdel(&seq);
    return result;
}

// eval_assignment
t_exp mx_assignment_variable(t_exp exp) {
    char *car = NULL;
    car = mx_left_exp(exp, "=");
    if (!mx_is_valid_parname(car)) {
        mx_strdel(&car);
        car = NULL;
    }
    return car;
}

t_exp mx_assignment_value(t_exp exp) {
    char *cdr = mx_right_exp(exp, "=");
    char *first_word = mx_first_word(cdr); // take the first word to left from '='
    mx_strdel(&cdr);
    return first_word;
}

t_exp mx_words_after_assignment(t_exp exp) {
    char *cdr = mx_right_exp(exp, "=");
    char *rest_words = mx_rest_words(cdr); // take the rest words to left from
    // '='
    mx_strdel(&cdr);
    return rest_words;
}

t_eval_result mx_eval_assignment(t_exp exp, t_global_environment *gv) {
    t_eval_result result = NULL;
    t_exp assignment_variable = mx_assignment_variable(exp);
    if (assignment_variable == NULL) { // если есть ошибка в имени переменной
        result = mx_simple_command(exp, gv, NULL, NULL);
    }
    else { // обрабатываем присвоение
        t_exp assignment_value = mx_assignment_value(exp);
        // save variable
        mx_env_set_var(assignment_variable, assignment_value, &(gv->vars));
        // check if other words
        t_exp words_after_assign = mx_words_after_assignment(exp);
        if (words_after_assign != NULL) {
            result = mx_eval(words_after_assign, gv, NULL, NULL);
        }
        else { // присвоение нормально, и нет слово после
            result = mx_new_evalresult();
        }
        mx_strdel(&words_after_assign);
        mx_strdel(&assignment_value);
    }
    mx_strdel(&assignment_variable);
    return result;
}

// Conditionals && ||. zsh calls it sublist
t_exp mx_if_predicate(t_exp exp) {
    char *op_name = mx_get_op_name(exp);
    char *car = mx_left_exp(exp, op_name);
    return car;
}

// for "&& pipeline"
t_exp mx_if_consequent(t_exp exp) {
    char *cdr = mx_right_exp(exp, "&&");
    return cdr;
}

// for "|| pipeline"
t_exp mx_if_alternative(t_exp exp) {
    char *cdr = mx_right_exp(exp, "||");
    return cdr;
}

bool mx_result_of_if_predicate(t_exp exp, t_global_environment *gv) {
    bool return_result;

    t_exp if_predicate = mx_if_predicate(exp);
    t_eval_result result_if_predicate = mx_eval(if_predicate, gv, NULL, NULL);
    // TODO: здесь надо ввести результат исполнения пайплайна
    if (result_if_predicate == NULL)
        return_result = true;
    else
        return_result = (result_if_predicate->status == true);

    mx_delete_evalresult(&result_if_predicate);
    mx_strdel(&if_predicate);
    return return_result;
}

// Conditionals
/**
 * a && b, if a ok then exec b
 * a || b  if b fail then exec b
 * @param exp
 * @return
 */
t_eval_result mx_eval_if(t_exp exp, t_global_environment *gv) {
    t_eval_result res = NULL;

    if (mx_result_of_if_predicate(exp, gv) == true) {
        // пайпа это тру и фолс

        t_exp if_consequent = mx_if_consequent(exp);
//        if (if_consequent != NULL) {
//            mx_printstr("\n");
//        }
        res = mx_eval(if_consequent, gv, NULL, NULL);
        mx_strdel(&if_consequent);
    }
    else {

        t_exp if_alternative = mx_if_alternative(exp);
//        if (if_alternative != NULL)
//            mx_printstr("\n");
        res = mx_eval(if_alternative, gv, NULL, NULL);
        mx_strdel(&if_alternative);
    }
    return res; // TODO: не знаю я прав или нет
}

// Sequences
/**
 * Sequences is a sequences of:
 * lists (delimiter is: ; &)
 * pipeline ( delimiter: is | )
 * of words (delimiter is space)
 */
t_eval_result
mx_eval_sequence(t_exp exps, t_global_environment *gv) {
    t_eval_result result = NULL;
    char *delim = ";";
    if (mx_is_last_exp(exps, delim)) {
        char *first_exp = mx_first_exp(exps, delim);
        result = mx_eval(first_exp, gv, NULL, NULL);
        mx_strdel(&first_exp);
    }
    else {
        char *first_exp = mx_first_exp(exps, delim);
        t_eval_result eval_fe = mx_eval(first_exp, gv, NULL, NULL);

//        if (mx_get_expressiontype_by_id(mx_get_binary_opid(exps)) == list)
//            mx_printstr("\n");

        char *rest_exps = mx_rest_exps(exps, delim);
        result = mx_eval_sequence(rest_exps, gv);

        mx_strdel(&rest_exps);
        mx_delete_evalresult(&eval_fe);
        mx_strdel(&first_exp);
    }
    return result; // TODO: не знаю что вернуть
}

//void print_pipe(char *exp, int *pipe_id, bool new_proc) {
//    if (pipe_id != NULL)
//        printf("this is '%s', ->%d ->%d new-proc=%d\n", exp, pipe_id[0],
//                pipe_id[1], new_proc);
//    else
//        printf("this is '%s', ->NULL new-proc=%d\n", exp, new_proc);
//}

// Piplines word word .. | word word .. | word word .. | word word ..
t_eval_result
mx_eval_seq_pipeline(t_exp exps, t_global_environment *gv, int *pipe_fd) {
    t_eval_result result = NULL;
    char *delim = "|";
    bool *new_proc = malloc(sizeof(bool));
    *new_proc = false;
    if (mx_is_last_exp(exps, delim)) {  // last right pipe
        char *first_exp = mx_first_exp(exps, delim);
//        if (pipe_fd != NULL) {
//            mx_smart_close_fd (&pipe_fd[1],1);
//        }
        result = mx_eval(first_exp, gv, pipe_fd, new_proc);
//        print_pipe(first_exp, pipe_fd, false);
        mx_strdel(&first_exp);
    }
    else {
        int *new_pipe_fd = mx_pipe_fd_new();
        pipe(new_pipe_fd);
        int *pipe_fd_forfistrexp = mx_pipe_fd_new();
        int *pipe_fd_forrestrexp = mx_pipe_fd_new();

        // left pipe
        char *first_exp = mx_first_exp(exps, delim);
//        printf("after: %s, [0]=%d [1]=%d\n", first_exp, new_pipe_fd[0],
//                new_pipe_fd[1]);
        if (pipe_fd == NULL) {
            //mx_smart_close_fd(&new_pipe_fd[0],0);
            pipe_fd_forfistrexp[0] = 0;
            pipe_fd_forfistrexp[1] = new_pipe_fd[0];
            pipe_fd_forrestrexp[0] = new_pipe_fd[1];
            pipe_fd_forrestrexp[1] = 1;
        }
        else {
//            printf("пришло pipe_fd[0]=%d, pipe_fd[1]=%d\n", pipe_fd[0],
//                    pipe_fd[1]);
            pipe_fd_forfistrexp[0] = pipe_fd[0];
            pipe_fd_forfistrexp[1] = new_pipe_fd[0];
            pipe_fd_forrestrexp[0] = new_pipe_fd[1];
            pipe_fd_forrestrexp[1] = 1;
        }
        *new_proc = true;
        t_eval_result eval_fe = mx_eval(first_exp, gv, pipe_fd_forfistrexp,
                                        new_proc);
//        print_pipe(first_exp, pipe_fd_forfistrexp, true);

        // right pipe
        char *rest_exps = mx_rest_exps(exps, delim);
        result = mx_eval_seq_pipeline(rest_exps, gv, pipe_fd_forrestrexp);

        // free
        mx_strdel(&rest_exps);
        mx_delete_evalresult(&eval_fe);
        mx_strdel(&first_exp);
        mx_pipe_fd_delete(&pipe_fd_forrestrexp);
        mx_pipe_fd_delete(&pipe_fd_forfistrexp);
        mx_pipe_fd_delete(&new_pipe_fd);
    }
    free(new_proc);
    return result; // TODO: не знаю что вернуть
}

//// ее можно переписть передавая в качестве аргумента фунцию eval or eval_word
//// TODO: delete
//t_eval_result
//mx_eval_sequence_ofwords(t_exp exps, char *delim, t_global_environment *gv) {
//    t_eval_result result = NULL;
//
//    if (mx_is_last_exp(exps, delim)) {
//        char *first_exp = mx_first_exp(exps, delim);
//        result = mx_eval_word(first_exp, gv);
//        mx_strdel(&first_exp);
//    }
//    else {
//        result = mx_new_evalresult();
//        char *first_exp = mx_first_exp(exps, delim);
//        t_eval_result eval_first_exp = mx_eval_word(first_exp, gv);
//        char *rest_exps = mx_rest_exps(exps, delim);
//        t_eval_result eval_rest_exps = mx_eval_sequence_ofwords(rest_exps,
//                delim, gv);
//
//        result->text = mx_strjoin_with_space(eval_first_exp->text,
//                                                  eval_rest_exps->text);
//        mx_delete_evalresult(&eval_rest_exps);
//        mx_strdel(&rest_exps);
//        mx_delete_evalresult(&eval_first_exp);
//        mx_strdel(&first_exp);
//    }
//    return result; // TODO: не знаю что вернуть
//}

void mx_copy(char c, char *newexp, int *index) {
    newexp[*index] = c;
    (*index)++;
}

// TODO: remove \ ' " from unquoted string
t_eval_result mx_eval_remove_escquotedquote(t_exp exp) {
    t_eval_result result = mx_new_evalresult();
    t_exp new_exp = mx_strnew(strlen(exp));
    int j = 0;
    e_mode mode = unquote;

    for (int i = 0; exp[i]; i++) {
        char c = exp[i];
        switch (exp[i]) {
            case '\\':
                if (mode == unquote) {
                    if (mx_count_esc(exp, i) % 2 != 0)
                        mx_copy('\\', new_exp, &j);
                }
                else if (mode == dquote) {
                    if (mx_count_esc(exp, i) % 2 == 0
                        && (exp[i + 1] != '\"' && exp[i + 1] != '\'') )
                        mx_copy('\\', new_exp, &j);
                }
                else
                    mx_copy('\\', new_exp, &j);
                break;
            case '\"':
                if (mode == unquote) {
                    if (mx_count_esc(exp, i) % 2 != 0)
                        mx_copy('\"', new_exp, &j);
                    else
                        mode = dquote;
                }
                else if (mode == dquote) {
                    if (mx_count_esc(exp, i) % 2 != 0)
                        mx_copy('\"', new_exp, &j);
                    else
                        mode = unquote;
                }
                else
                    mx_copy('\"', new_exp, &j);
                break;
            case '\'':
                if (mode == unquote) {
                    if (mx_count_esc(exp, i) % 2 != 0)
                        mx_copy('\'', new_exp, &j);
                    else
                        mode = quote;
                }
                else if (mode == dquote) {
                    mx_copy('\\', new_exp, &j);
                }
                else if (mode == quote)
                    mode = unquote;
                break;
            default:
                mx_copy(exp[i], new_exp, &j);
                break;
        }
    }
    if (mode != unquote) {
        result->status = false;
        mx_strdel(&new_exp);
        result->text = NULL;
    }
    else
        result->text = new_exp;
    return result;
}

// Procedure arguments
void mx_list_of_values(t_list_of_values **list,
                       t_exp exps, t_global_environment *gv) {
    if (mx_is_last_word(exps)) {
        return; // end of list
    }
    else {
        t_exp first_word = mx_first_word(exps);
        t_eval_result eval_first_result = mx_eval_remove_escquotedquote(
                first_word);
        t_exp rest_words = NULL;

        if (eval_first_result->text != NULL)
            mx_liststr_push_back(list, eval_first_result->text, NULL);
        rest_words = mx_rest_words(exps);
        //if (rest_operands != NULL)
            mx_list_of_values(list, rest_words, gv);

        mx_strdel(&rest_words);
        mx_delete_evalresult(&eval_first_result);
        mx_strdel(&first_word);
    }
}


// for eval
t_eval_result
mx_simple_command(t_exp expression, t_global_environment *gv, int *pipe_fd,
                  bool *new_proc) {
    t_eval_result result = NULL;
    t_list_of_values *list_of_arguments = NULL;
    t_exp command = NULL;
    t_eval_result eval_operator = NULL;
    t_exp operands = NULL;
    t_redirect *redirections = NULL;
    t_exp exp = strdup(expression);
//    bool fork_process = false;
    t_config *cnf;

    cnf = mx_config_new();
    cnf->pipe_fd = pipe_fd;
    cnf->new_proc = new_proc;
    gv->cnf = cnf;
    mx_alias_expansion(&exp, gv);
    mx_parameter_expansion(&exp, gv);
    //mx_command_substitution(&exp, gv, new_proc);
    //mx_file_expansion(&exp, gv);
    if (!mx_extract_redirections(&exp, &redirections)) {
        result = mx_new_evalresult();
        result->status = false;
    }
    else {
        command = mx_command(exp);
        //eval_operator = mx_eval_word(operator, gv);
        operands = mx_operands(exp);
        mx_list_of_values(&list_of_arguments, operands, gv);
        // apply
        gv->cnf->redirections = redirections;
        result = mx_apply(command, list_of_arguments, gv);
    }
    mx_strdel(&exp);
    mx_delete_redirect(&redirections);
    mx_strdel(&operands);
    mx_delete_evalresult(&eval_operator);
    mx_strdel(&command);
    mx_liststr_delete(&list_of_arguments);
    mx_delete_config(&cnf);
    return result;
}

// -----------------------    apply ------

t_eval_result
mx_apply(char *command, t_list_of_values *arguments, t_global_environment *gv) {
    t_eval_result result = NULL;
    int argc;
    char **argv = NULL;
//    t_config *cnf = NULL;

    mx_convert_strlist_strvector(arguments, &argv, &argc);
    gv->cnf->agv = argv;
    gv->cnf->agvsize = argc;
//    cnf = mx_config_new();
//    gv->cnf = cnf;
    result = mx_execute(command, gv);
//    mx_delete_config(&cnf);
    mx_delete_strvector(&argv, &argc);
    return result; // TODO: это заглушка
}

// -------   eval

//t_eval_result mx_eval_word(t_exp exp, t_global_environment *gv) {
//    if (exp == NULL)
//        return NULL;
//
//    t_eval_result result = NULL;
//    int status;
//    e_exp_type parse = mx_get_expressiontype_by_id(mx_get_word_id(exp));
//
//    switch (parse) {
//        case self_evaluating:
//            result = mx_self_evaluating(exp, gv);
//            break;
//        case quoted_string:
//            result = mx_text_of_quotation(exp, gv);
//            break;
//        case double_quoted_string:
//            result = mx_eval_doublequote(exp, gv);
//            break;
//        case variable_substitution:
//            result = mx_lookup_variable_value(exp, gv);
//            break;
//        case command_substitution:
//            result = mx_eval_command_substitution(exp, gv);
//            break;
//        case file_extension:
//            result = mx_file_extension(exp, gv);
//            break;
//        default:
//            result = mx_new_evalresult();
//            result->text = strdup("Не могу распарсить слово");
//            result->status = false; // ошибка
//    }
//    return result;
//}

t_eval_result
mx_eval(t_exp exp, t_global_environment *gv, int *pipe_fd, bool *new_proc) { // TODO:  передавать по ссылке
    if (exp == NULL || exp[0] == '\0' || exp[0] == '\n')
        return NULL;

    t_eval_result result = NULL;
    int status;
    e_exp_type exp_type = mx_get_expressiontype_by_id(mx_get_binary_opid(exp));
    // проверка по бинарным операциям

    switch (exp_type) {
        case variable_assignment:
            result = mx_eval_assignment(exp, gv);
            break;
        case pipeline: // simple_command | simple_command | simple_command
            result = mx_eval_seq_pipeline(exp, gv, NULL);
            break;
        case sublist: // || &&
            result = mx_eval_if(exp, gv);
            break;
        case list: // ;
            //ss = mx_begin_actions(exp); //TODO: не знаю зачем begin_action
            result = mx_eval_sequence(exp, gv);
            break;
        case simple_command: //simple_command:
            result = mx_simple_command(exp, gv, pipe_fd, new_proc);
            break;
        default:
            result = mx_new_evalresult();
            result->text = strdup("Не могу распарсить");
            result->status = false; // ошибка
    }
    return result;
}

//int main(void) {
//    t_exp exp;
//    t_environment *env;
//
//    //exp = "ls ~ > test.txt | $(echo ~) | cat -e  && echo ok|| echo error; "
//    //       exp = " $name ";
//    exp = "$(one `tow; three`)  ";
//    printf("-> %s\n\n", exp);
//    env = mx_env_new();
//    t_eval_result result = mx_eval(exp, env);
//    mx_delete_evalresult(&result);
//
//    printf("\nSUCCESS\n----\n");
//    //system("leaks -q parser");
//
//    return 0;
//}

// test file_extension
//int main(void) {
//    t_exp exp;
//    t_global_environment *gv = mx_new_global_env();
//    exp = strdup("catt ~/bin && echo 1 || echo 2");
//    t_eval_result result = mx_eval(exp, gv);
//    mx_delete_evalresult(&result);
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}

////test eval_remove_escquotedquote
//#include <assert.h>
//int main(void) {
//    t_exp exp;
//    char *arr[] =  {
//            "oo\\\\\"oo\\\"oo\"", "oo\'oo\\\"oo\'oo",
//            "-\'-\\-\'", "o\'o\\\\o\'", "o\'o\\\\\\o\'",
//            "-\"-\\-\"", "o\"o\\\\o\"", "o\"o\\\\\\o\"",
//            "oo\\", "oo\\\\", "oo\\\\\\", "oo\\\\\\\\",
//
//
//            NULL};
//    char *test[] = {
//            "oo\\oo\"oo", "oooo\\\"oooo",
//            "--\\-", "oo\\\\o", "oo\\\\\\o",
//            "--\\-", "oo\\o", "oo\\\\o",
//            "oo", "oo\\", "oo\\", "oo\\\\",
//
//
//                   };
//    for (int i = 0; arr[i]; i++) {
//        exp = strdup(arr[i]);
//        t_eval_result result = mx_eval_remove_escquotedquote(exp);
//        printf("test %d) <<%s>>\n", i+1, result->text);
//        assert(strcmp(result->text, test[i]) == 0);
//        free(exp);
//        mx_delete_evalresult(&result);
//    }
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush_metacicle_evaluator");
//    return 0;
//}
