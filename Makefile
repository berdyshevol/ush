NAME = ush

NLIB = Libmx/libmx.a

HDR = ush.h \
      i.h \
      o.h \
      p.h \
	  liststr.h \
	  environment.h \


SRC =   main.c \
        mx_builtins.c \
		mx_builtin_export.c \
		mx_builtin_cd.c \
		mx_builtin_pwd.c \
	    mx_driver_loop.c \
		mx_env_delete.c \
		mx_env_get_value.c \
		mx_env_init.c \
		mx_env_set_var.c \
		mx_eval.c \
		mx_free_all.c \
		mx_init_shell.c \
		mx_liststr_delete.c \
		mx_liststr_init.c \
		mx_liststr_pop_front.c \
		mx_liststr_push_front.c \
		mx_new_global_env.c \
		mx_output.c \
		mx_print_prompt.c \
		mx_read_input.c \
		mx_is_closed_expression.c \
		mx_sort_arr.c \
		mx_check_buffer.c \
		mx_builtin_echo.c \


OBJ = $(SRC:.c=.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror 

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