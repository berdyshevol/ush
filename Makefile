NAME = ush

NLIB = Libmx/libmx.a

HDR = ush.h \
      i.h \
      o.h \
      p.h \

SRC = main.c \
      mx_init_shell.c \
      mx_driver_loop.c \
      mx_free_all.c \
      mx_new_env.c \
      mx_print_prompt.c \
      mx_eval.c \
      mx_read_input.c \

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