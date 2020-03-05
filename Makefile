NAME = ush

NLIB = Libmx/libmx.a

HDR = environment.h \
      evaluator.h \
      i.h \
      liststr.h \
      p.h \
      parser.h \
      ush.h \


SRC =   main.c \
mx_builtin_cd.c \
mx_builtin_echo.c \
mx_builtin_env.c \
mx_builtin_export.c \
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
mx_eval_file_expansion.c \
mx_eval_parameter_expansion.c \
mx_eval_redirections.c \
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
mx_parse_words_sequence.c \
mx_parser_assignment.c \
mx_parser_find_file_expansion.c \
mx_parser_find_param.c \
mx_parser_firstword.c \
mx_parser_get_binary_opid.c \
mx_parser_get_op_id.c \
mx_parser_get_op_name.c \
mx_parser_get_operator_info_byid.c \
mx_parser_get_unary_opid.c \
mx_parser_has_expression_operator.c \
mx_parser_is_closed_expression.c \
mx_parser_smart_find.c \
mx_parser_split_two_str.c \
mx_parser_strstr_esc.c \
mx_parser_trim.c \
mx_parser_wordchain.c \
mx_print_prompt.c \
mx_read_input.c \
mx_sort_arr.c \
mx_strjoin_with_space.c \
mx_builtin_fg.c \
mx_builtin_fg2.c \

OBJ = $(SRC:.c=.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror -Wunused-parameter
#CFLAG = -std=c11 -Wunused-parameter -Wsign-compare -Wunused-function -Wunused-variable

all: install clean

install:
	@cd libmx && make -f Makefile install
	@cp $(addprefix src/, $(SRC)) $(addprefix inc/, $(HDR)) Libmx/inc/libmx.h .
	@clang $(CFLAG) -c $(SRC) -I $(HDR)
	@mkdir obj
	@clang $(CFLAG) $(OBJ) $(NLIB) -o $(NAME)
	@mv $(OBJ) ./obj
	@rm -rf libmx.h $(SRC) $(HDR)
	@rm *.gch

uninstall: clean
	@cd libmx && make -f Makefile uninstall
	@rm -rf $(NAME)

clean:
	@cd libmx && make -f Makefile clean
	@rm -rf $(OBJ)
	@rm -rf ./obj

reinstall: uninstall install

cl:
	@rm *.c *.h *.o