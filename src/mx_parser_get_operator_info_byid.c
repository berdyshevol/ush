#include "parser.h"

static t_bind_operatorid_name_type bind(int i) {
    static t_bind_operatorid_name_type bind[] = {
            {semicolon,            ";",  list},
//            {ampersand,            "&",  simple_command},
            {and_and,              "&&", sublist},
            {or_or,                "||", sublist},
            {pipe_operator,        "|",  pipeline},
            {pipe_ampersand,       "|&", pipeline},

            {all_binary_operators, NULL, all_binary_type},

            {no_operator,          NULL, simple_command},
            {parameter_assignment, "=",  variable_assignment},
            {unclosed_expression,  "",   unclosed_exp_type},
            {operator_id_count,    "",   expression_type_count}
    };
    return bind[i];
}

char *mx_get_name_by_id(e_operator_id operator_name) {
    for (int i = 0; bind(i).expression_type != expression_type_count; i++) {
        if (i == (int)operator_name)
            return bind(i).name;
    }
    return NULL;
}

e_exp_type mx_get_expressiontype_by_id(e_operator_id operator_id) {
    for (int i = 0; bind(i).expression_type != expression_type_count; i++) {
        if (i == (int)operator_id)
            return (e_exp_type) bind(i).expression_type;
    }
    return expression_type_count;
}


// #include <assert.h>
// int main(void) {
//    printf("Test expression type\n");
//
//    char *exp[] = {"  'name' ",     "\"name\" ",     " $(name)",
//                   " `cmd`",        " ~/name",      "$(kdkd",
//                   "ls",            " ls ",         "cat ~/bin",
//                  NULL};
//    e_exp_type res[] =
//            {quoted_string, double_quoted_string,   command_substitution,
//             command_substitution, file_extension,  unclosed_exp_type  ,
//             self_evaluating,      self_evaluating, simple_command
//    };
//     for (int i = 0; exp[i]; i++) {
//         if (i == 5) {
//             printf("");
//         }
//         e_operator_id id = mx_get_word_id(exp[i]);
//         e_exp_type type = mx_get_expressiontype_by_id(id);
//
//         printf("%d) <<%s>> %d (%d)\n",i+1, exp[i], type, res[i]);
//         assert(type == res[i]);
//     }
//
//    printf("\nSUCCESS\n----\n");
//
//    system("leaks -q ush_metacicle_evaluator");
//
//    return 0;
// }
