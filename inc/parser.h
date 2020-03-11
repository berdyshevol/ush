#ifndef PARSER_H
#define PARSER_H

#include "libmx.h"
#include <string.h>

typedef enum {
    semicolon,                //    ;
    ampersand,                //    &
    and_and,                  //    &&
    or_or,                    //    ||
    pipe_operator,            //    |
    pipe_ampersand,           //    |&
    all_binary_operators,
    quote_op,                    //    '..'
    doublequote,              //    ".."  
    dollar_curly_bracket,     //    ${..}
    dollar_parathesese,       //    $(..)
    dollar_name,              //    $name
    backquote,                // ` .. `
    tilda,                    //    ~
    no_operator,
    parameter_assignment,     //    =
    string,
    unclosed_expression,
    operator_id_count
} e_operator_id;

typedef enum {
    list,
    sublist,
    pipeline,
    simple_command,
    command_name,
    command_args,
    redirections,
    word,
    variable_assignment,
    function_definition,
    file_extension,
    command_substitution,
    variable_substitution,
    alias,
    double_quoted_string,
    quoted_string,
    self_evaluating,
    all_binary_type,
    unclosed_exp_type,
    expression_type_count
} e_exp_type;

typedef enum {
    unquote,
    dquote,
    quote
} e_mode;

typedef struct {
    e_operator_id operator_id;
    char *name;
    e_exp_type expression_type;
} t_bind_operatorid_name_type;


typedef enum {
    return_true,
    break_loop,
    continue_loop
} e_return;

typedef struct {
    int start;
    int end;
    char *name;
} t_args;

bool mx_is_whitespace(char c);

// parse binary operators
e_operator_id mx_get_binary_opid(char *exp);
char *mx_get_name_by_id(e_operator_id operator_name);
char *mx_get_op_name(char *exp);
e_exp_type mx_get_expressiontype_by_id(e_operator_id operator_name);

// parameter assignment
bool mx_has_assignment(char *exp);
bool mx_is_valid_parname(char *exp);
bool mx_isalpha(char c);

bool mx_has_expression_operator(char *exp, char *operator);
bool mx_is_closed_expression(char *s);

char *mx_smart_find(char *exp, char *sbstr);
void mx_split_two_str(char *exp, char *operator,
                      char **left_string, char **right_string);
char *mx_strjoin_with_space(char *s1, char *s2);
char *mx_left_exp(char *exp, char *delim);
char *mx_right_exp(char *exp, char *delim);

// word chain sequence
void mx_parse_words_sequence(char *exp, char **f_wordchain, char **splitter, char **r_wordchains);
char *mx_first_word(char *exp);
bool mx_is_last_word(char *exp);
char *mx_rest_words(char *exp);


void mx_trimleft(char **str);

// parameter substitution
bool mx_find_param(char *exp, int *start, int *end, char **name);

// command substitution
bool mx_find_command_substitution(char *exp, int *start, int *end, char **name);
e_return mx__cmdsubs_type_one(char *exp, int i, t_args *args);
e_return mx__cmdsubs_type_two(char *exp, int i, t_args *args);

// file expansion
bool mx_find_file_expansion(char *exp, int *start, int *end, char **name);

// miscellaneous
void mx_reset(int *a, int *b, char **s);
void mx_set(t_args *args, int *start, int *end, char **name);
t_args *mx_args_new(void);
void mx_args_delete(t_args **args);
char *mx_strstr_esc(char *exp, char *substr);
int mx_count_esc(char *exp, int position);
void mx_change_mode(e_mode *mode, char *exp, int pos);

// print error messages
void mx_print_oddnumberofquotes();

#endif
