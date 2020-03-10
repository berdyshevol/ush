//
// Created by Oleg Berdyshev on 1/29/20.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H


#include "libmx.h"
#include "ush.h"
#include "parser.h"

typedef char* t_exp;

typedef t_liststr t_list_of_values; // TODO: or char*

typedef enum {
    less,          //    <
    less_less,     //    <<
    more,          //    >
    more_more,     //    >>
    two_more,      //    2>
    less_more      //    <>
} e_redirection_chars;


// parsing
e_exp_type mx_parse(t_exp exp);

// words
t_eval_result mx_self_evaluating (t_exp exp, t_global_environment *env);
t_eval_result mx_text_of_quotation(t_exp exp, t_global_environment *gv);

// Expansions
t_eval_result mx_lookup_variable_value(t_exp exp, t_global_environment *gv);
t_eval_result  mx_eval_command_substitution(t_exp exp, t_global_environment *gv);
t_eval_result mx_file_extension(t_exp exp, t_global_environment *gv);

// Begin packages a sequence of expressions into a single expression.
t_exp mx_first_exp(t_exp seq, char *delim);

bool mx_is_last_exp(t_exp seq, char *delim);
t_exp mx_rest_exps(t_exp seq, char *delim);

// eval_assignment
t_eval_result mx_eval_assignment(t_exp exp, t_global_environment *gv);
t_exp mx_assignment_variable(t_exp exp);
t_exp mx_assignment_value(t_exp exp);
t_exp mx_words_after_assignment(t_exp exp);
void mx_parameter_expansion(t_exp *exp, t_global_environment *gv);
void mx_insert(char **exp, int start, int end, char *word);

// A procedure application is simple-command
t_exp mx_command(t_exp exp);
t_exp mx_operands(t_exp exp);

// Conditionals && ||. zsh calls it sublist
t_exp mx_if_predicate(t_exp exp);
t_exp mx_if_consequent(t_exp exp);
t_exp mx_if_alternative(t_exp exp);
bool mx_result_of_if_predicate(t_exp exp, t_global_environment *gv);

// Conditionals
t_eval_result mx_eval_if(t_exp exp, t_global_environment *gv);

// Sequences
t_eval_result
mx_eval_sequence(t_exp exps, t_global_environment *gv);
t_eval_result
mx_eval_seq_pipeline(t_exp exps, t_global_environment *gv, int *pipe_fd);

//Procedure arguments
void mx_list_of_values(t_list_of_values **list,
                       t_exp exps, t_global_environment *gv);

// for eval
t_eval_result
mx_simple_command(t_exp expression, t_global_environment *gv, int *pipe_fd,
                  bool *new_proc);
t_eval_result
mx_eval(t_exp exp, t_global_environment *gv, int *pipe_fd, bool *new_proc);

        t_eval_result mx_new_evalresult(void);
void mx_delete_evalresult(t_eval_result *eval_result);

// apply
t_eval_result mx_apply(char *command, t_list_of_values *arguments,
                       t_global_environment *gv);

// redirections
t_redirect *mx_new_redirect(char **exp, bool *error);
void mx_delete_redirect(t_redirect **redirect);
bool mx_extract_redirections(t_exp *exp, t_redirect **redirections);
void mx_extract_error(char **exp, t_redirect **redirect, bool *er);
void mx_extract_input(char **exp, t_redirect **redirect, bool *er);
void mx_extract_output(char **exp, t_redirect **redirect, bool *er);
bool mx_extract_helper(char *str_value,char **str_field,
                       bool bool_value, bool *bool_field);
void mx_delete_arlere(char **after_redirect,
                      char **left_exp, char **right_exp);
bool mx_apply_redirect(t_redirect *redir);
void mx_reset_redirections(t_redirect *redir);
void mx_apply_error(t_redirect *redir, bool *res);

// file expansion
void mx_file_expansion(t_exp *exp);

// command substitution
void mx_command_substitution(t_exp *exp, t_eval_result result,
                             t_global_environment *gv);

#endif //USH_UTILS_EVALUATOR_H
