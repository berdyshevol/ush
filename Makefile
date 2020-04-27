NAME = ush

NLIB = libmx
PLIB = Libmx/$(NLIB).a

SRCD = src
INCD = inc
OBJD = obj

LBMXINC = $(NLIB).h

INC = environment.h \
      evaluator.h \
      i.h \
      liststr.h \
      p.h \
      parser.h \
      ush.h \


SRC =   main.c \
		mx_builtin_cd.c \
		mx_builtin_echo.c \
		mx_builtin_echo2.c \
		mx_builtin_env.c \
		mx_builtin_exit.c \
		mx_builtin_export.c \
		mx_builtin_fg.c \
		mx_builtin_fg2.c \
		mx_builtin_jobs.c \
		mx_builtin_pwd.c \
		mx_builtin_which.c \
		mx_builtins.c \
		mx_check_buffer.c \
		mx_driver_loop.c \
		mx_env_get_value.c \
		mx_env_new_delete.c \
		mx_env_set_var.c \
		mx_environ_copy.c \
		mx_eval.c \
		mx_eval_assignment.c \
		mx_eval_command_substitution.c \
		mx_eval_file_expansion.c \
		mx_eval_logics.c \
		mx_eval_parameter_expansion.c \
		mx_eval_redirections1.c \
		mx_eval_redirections2.c \
		mx_eval_redirections3.c \
		mx_eval_redirections4.c \
		mx_eval_redirections5.c \
		mx_eval_sequence.c \
		mx_eval_sequence_pipeline.c \
		mx_eval_simple_command1.c \
		mx_eval_simple_command2.c \
		mx_eval_simple_command3.c \
		mx_eval_simple_command4.c \
		mx_exec_apply_pipe.c \
		mx_exec_try_bin.c \
		mx_execute.c \
		mx_free_all.c \
		mx_global_env_new_delete.c \
		mx_history.c \
		mx_init_shell.c \
		mx_liststr_convert_argv.c \
		mx_liststr_delete.c \
		mx_liststr_init.c \
		mx_liststr_length.c \
		mx_liststr_pop_front.c \
		mx_liststr_push_back.c \
		mx_liststr_push_front.c \
		mx_new_delete_config.c \
		mx_new_evalresult.c \
		mx_parse_words_sequence1.c \
		mx_parse_words_sequence2.c \
		mx_parser_assignment.c \
		mx_parser_change_mode.c \
		mx_parser_find_command_substitution1.c \
		mx_parser_find_command_substitution2.c \
		mx_parser_find_command_substitution3.c \
		mx_parser_find_file_expansion.c \
		mx_parser_find_param.c \
		mx_parser_get_binary_opid.c \
		mx_parser_get_op_name.c \
		mx_parser_get_operator_info_byid.c \
		mx_parser_has_expression_operator.c \
		mx_parser_is_closed_expression.c \
		mx_parser_smart_find.c \
		mx_parser_split_two_str.c \
		mx_parser_strstr_esc.c \
		mx_parser_trim.c \
		mx_print_prompt.c \
		mx_print_error_messages.c \
		mx_read_input.c \
		mx_sort_arr.c \
		mx_strjoin_with_space.c \
		mx_get_var_part.c \
        mx_match_search.c \
        mx_export_var_to_lists.c \
        mx_flags_map.c \
        mx_path_cancat.c \
        mx_flags_handler_cd.c \
        mx_flags_handler_env.c \
        mx_environ_handler_env.c \
        mx_exec_env.c \
		mx_flags_settings_cd.c \

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SRCD)/, $(SRC))
INCS = $(addprefix $(INCD)/, $(INC))
LBMXP = Libmx/inc/$(NLIB).h

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror -Wunused-parameter

all: install clean

install:
	@make -sC $(NLIB) install
	@cp $(SRCS) $(INCS) $(LBMXP) .
	@clang $(CFLAG) -c $(SRC) -I $(INC)
	@mkdir $(OBJD)
	@clang $(CFLAG) $(OBJ) $(PLIB) -o $(NAME)
	@mv $(OBJ) $(OBJD)
	@rm -rf $(LBMXINC) $(SRC) $(INC) *.gch

uninstall: clean
	@make -sC $(NLIB) $@
	@rm -rf $(NAME)

clean:
	@make -sC $(NLIB) $@
	@rm -rf $(OBJ) $(OBJD)

reinstall: uninstall install
