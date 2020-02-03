#include "ush.h"

void mx_reset_input_mode(void) {
	tcsetattr(0, TCSANOW, &stored_settings);
}

static void set_input_mode (void) {
	struct termios new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= ~(ICANON|ECHO|ISIG);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, &new_settings);
}

void mx_init_shell(t_global_environment *gv) {
    set_input_mode();
    setvbuf(stdout, NULL, _IONBF, 0);
    gv->shellName = "brothers' shell"; // TODO: удалить
    // настройка сигналов
}
