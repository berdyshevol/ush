#ifndef PARSER_H
#define PARSER_H

//#include "ush.h"
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
    string_type,
    esc_type,
    file_expansion_type,
    dquote_type,
    unclosed_expression_type
} e_word_type;

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

char mx_whitespace(int i);
char mx_slash_plus_symbol(int i);
bool mx_is_whitespace(char c);
bool mx_can_skip(char c);
bool mx_can_trim(int i, char *s);

//e_operator_id mx_get_op_id(char *exp); deprecated function
e_operator_id mx_get_binary_opid(char *exp);
e_operator_id mx_get_unary_opid(char *exp);
//e_operator_id mx_get_word_id(char *exp);

bool mx_has_assignment(char *exp);
bool mx_is_valid_parname(char *exp);
bool mx_isalpha(char c);
//bool mx_is_valid_pathname(char *exp);
char *mx_extract_unary_operand(char *exp);
//bool mx_has_open_closing_exp(char *exp, char *open, char *closing);
char *mx_get_name_by_id(e_operator_id operator_name);
char *mx_get_op_name(char *exp);
e_exp_type mx_get_expressiontype_by_id(e_operator_id operator_name);
bool mx_has_expression_operator(char *exp, char *operator);
bool mx_is_closed_expression(char *s);
//int mx_is_opening(int i, char *s, int count_slash);
//int mx_is_closing(int i, char *s, int count_slash);
void mx_get_first_word(char *exp, char **first_word, char **rest_exp);
bool mx_is_single_char(char c);
char *mx_smart_find(char *exp, char *op);
void mx_split_two_str(char *exp, char *operator,
                      char **left_string, char **right_string);
char *mx_strjoin_with_space(char *s1, char *s2);
char *mx_left_exp(char *exp, char *delim);
char *mx_trim(char *s);
char *mx_right_exp(char *exp, char *delim);

// word chain sequence
void mx_parse_words_sequence(char *exp, char **f_wordchain, char **splitter, char **r_wordchains);
char *mx_first_word(char *exp);
bool mx_is_last_word(char *exp);
char *mx_rest_words(char *exp);
void mx_trimleft(char **str);


// parameter
bool mx_find_param(char *exp, int *start, int *end, char **name);

// command substitution
bool mx_find_command_substitution(char *exp, int *start, int *end, char **name);

// file expansion
bool mx_find_file_expansion(char *exp, int *start, int *end, char **name);

// miscellaneous
void mx_reset(int *a, int *b, char **s);
void mx_set(t_args *args, int *start, int *end, char **name);
t_args *mx_args_new(void);
void mx_args_delete(t_args **args);
char *mx_strstr_esc(char *exp, char *substr);
//char *mx_strstr_esc_rev(char *exp, char *substr);
int mx_count_esc(char *exp, int position);
void mx_change_mode(e_mode *mode, char *exp, int pos);

// print error messages
void mx_print_oddnumberofquotes();

#endif
