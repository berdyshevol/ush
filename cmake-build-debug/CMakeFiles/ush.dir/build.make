# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/ihumeniuk/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/ihumeniuk/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ihumeniuk/Desktop/work

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ihumeniuk/Desktop/work/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ush.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ush.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ush.dir/flags.make

CMakeFiles/ush.dir/src/main.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ush.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/main.c.o   -c /Users/ihumeniuk/Desktop/work/src/main.c

CMakeFiles/ush.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/main.c > CMakeFiles/ush.dir/src/main.c.i

CMakeFiles/ush.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/main.c -o CMakeFiles/ush.dir/src/main.c.s

CMakeFiles/ush.dir/src/mx_builtin_cd.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_builtin_cd.c.o: ../src/mx_builtin_cd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ush.dir/src/mx_builtin_cd.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_builtin_cd.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_builtin_cd.c

CMakeFiles/ush.dir/src/mx_builtin_cd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_builtin_cd.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_builtin_cd.c > CMakeFiles/ush.dir/src/mx_builtin_cd.c.i

CMakeFiles/ush.dir/src/mx_builtin_cd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_builtin_cd.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_builtin_cd.c -o CMakeFiles/ush.dir/src/mx_builtin_cd.c.s

CMakeFiles/ush.dir/src/mx_builtin_echo.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_builtin_echo.c.o: ../src/mx_builtin_echo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ush.dir/src/mx_builtin_echo.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_builtin_echo.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_builtin_echo.c

CMakeFiles/ush.dir/src/mx_builtin_echo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_builtin_echo.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_builtin_echo.c > CMakeFiles/ush.dir/src/mx_builtin_echo.c.i

CMakeFiles/ush.dir/src/mx_builtin_echo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_builtin_echo.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_builtin_echo.c -o CMakeFiles/ush.dir/src/mx_builtin_echo.c.s

CMakeFiles/ush.dir/src/mx_builtin_export.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_builtin_export.c.o: ../src/mx_builtin_export.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ush.dir/src/mx_builtin_export.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_builtin_export.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_builtin_export.c

CMakeFiles/ush.dir/src/mx_builtin_export.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_builtin_export.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_builtin_export.c > CMakeFiles/ush.dir/src/mx_builtin_export.c.i

CMakeFiles/ush.dir/src/mx_builtin_export.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_builtin_export.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_builtin_export.c -o CMakeFiles/ush.dir/src/mx_builtin_export.c.s

CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o: ../src/mx_builtin_pwd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_builtin_pwd.c

CMakeFiles/ush.dir/src/mx_builtin_pwd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_builtin_pwd.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_builtin_pwd.c > CMakeFiles/ush.dir/src/mx_builtin_pwd.c.i

CMakeFiles/ush.dir/src/mx_builtin_pwd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_builtin_pwd.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_builtin_pwd.c -o CMakeFiles/ush.dir/src/mx_builtin_pwd.c.s

CMakeFiles/ush.dir/src/mx_builtins.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_builtins.c.o: ../src/mx_builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ush.dir/src/mx_builtins.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_builtins.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_builtins.c

CMakeFiles/ush.dir/src/mx_builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_builtins.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_builtins.c > CMakeFiles/ush.dir/src/mx_builtins.c.i

CMakeFiles/ush.dir/src/mx_builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_builtins.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_builtins.c -o CMakeFiles/ush.dir/src/mx_builtins.c.s

CMakeFiles/ush.dir/src/mx_check_buffer.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_check_buffer.c.o: ../src/mx_check_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ush.dir/src/mx_check_buffer.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_check_buffer.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_check_buffer.c

CMakeFiles/ush.dir/src/mx_check_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_check_buffer.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_check_buffer.c > CMakeFiles/ush.dir/src/mx_check_buffer.c.i

CMakeFiles/ush.dir/src/mx_check_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_check_buffer.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_check_buffer.c -o CMakeFiles/ush.dir/src/mx_check_buffer.c.s

CMakeFiles/ush.dir/src/mx_driver_loop.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_driver_loop.c.o: ../src/mx_driver_loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/ush.dir/src/mx_driver_loop.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_driver_loop.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_driver_loop.c

CMakeFiles/ush.dir/src/mx_driver_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_driver_loop.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_driver_loop.c > CMakeFiles/ush.dir/src/mx_driver_loop.c.i

CMakeFiles/ush.dir/src/mx_driver_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_driver_loop.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_driver_loop.c -o CMakeFiles/ush.dir/src/mx_driver_loop.c.s

CMakeFiles/ush.dir/src/mx_env_delete.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_env_delete.c.o: ../src/mx_env_delete.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/ush.dir/src/mx_env_delete.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_env_delete.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_env_delete.c

CMakeFiles/ush.dir/src/mx_env_delete.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_env_delete.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_env_delete.c > CMakeFiles/ush.dir/src/mx_env_delete.c.i

CMakeFiles/ush.dir/src/mx_env_delete.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_env_delete.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_env_delete.c -o CMakeFiles/ush.dir/src/mx_env_delete.c.s

CMakeFiles/ush.dir/src/mx_env_get_value.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_env_get_value.c.o: ../src/mx_env_get_value.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/ush.dir/src/mx_env_get_value.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_env_get_value.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_env_get_value.c

CMakeFiles/ush.dir/src/mx_env_get_value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_env_get_value.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_env_get_value.c > CMakeFiles/ush.dir/src/mx_env_get_value.c.i

CMakeFiles/ush.dir/src/mx_env_get_value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_env_get_value.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_env_get_value.c -o CMakeFiles/ush.dir/src/mx_env_get_value.c.s

CMakeFiles/ush.dir/src/mx_env_init.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_env_init.c.o: ../src/mx_env_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/ush.dir/src/mx_env_init.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_env_init.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_env_init.c

CMakeFiles/ush.dir/src/mx_env_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_env_init.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_env_init.c > CMakeFiles/ush.dir/src/mx_env_init.c.i

CMakeFiles/ush.dir/src/mx_env_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_env_init.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_env_init.c -o CMakeFiles/ush.dir/src/mx_env_init.c.s

CMakeFiles/ush.dir/src/mx_env_set_var.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_env_set_var.c.o: ../src/mx_env_set_var.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/ush.dir/src/mx_env_set_var.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_env_set_var.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_env_set_var.c

CMakeFiles/ush.dir/src/mx_env_set_var.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_env_set_var.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_env_set_var.c > CMakeFiles/ush.dir/src/mx_env_set_var.c.i

CMakeFiles/ush.dir/src/mx_env_set_var.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_env_set_var.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_env_set_var.c -o CMakeFiles/ush.dir/src/mx_env_set_var.c.s

CMakeFiles/ush.dir/src/mx_eval.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_eval.c.o: ../src/mx_eval.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/ush.dir/src/mx_eval.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_eval.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_eval.c

CMakeFiles/ush.dir/src/mx_eval.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_eval.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_eval.c > CMakeFiles/ush.dir/src/mx_eval.c.i

CMakeFiles/ush.dir/src/mx_eval.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_eval.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_eval.c -o CMakeFiles/ush.dir/src/mx_eval.c.s

CMakeFiles/ush.dir/src/mx_free_all.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_free_all.c.o: ../src/mx_free_all.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/ush.dir/src/mx_free_all.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_free_all.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_free_all.c

CMakeFiles/ush.dir/src/mx_free_all.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_free_all.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_free_all.c > CMakeFiles/ush.dir/src/mx_free_all.c.i

CMakeFiles/ush.dir/src/mx_free_all.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_free_all.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_free_all.c -o CMakeFiles/ush.dir/src/mx_free_all.c.s

CMakeFiles/ush.dir/src/mx_history.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_history.c.o: ../src/mx_history.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/ush.dir/src/mx_history.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_history.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_history.c

CMakeFiles/ush.dir/src/mx_history.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_history.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_history.c > CMakeFiles/ush.dir/src/mx_history.c.i

CMakeFiles/ush.dir/src/mx_history.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_history.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_history.c -o CMakeFiles/ush.dir/src/mx_history.c.s

CMakeFiles/ush.dir/src/mx_init_shell.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_init_shell.c.o: ../src/mx_init_shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/ush.dir/src/mx_init_shell.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_init_shell.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_init_shell.c

CMakeFiles/ush.dir/src/mx_init_shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_init_shell.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_init_shell.c > CMakeFiles/ush.dir/src/mx_init_shell.c.i

CMakeFiles/ush.dir/src/mx_init_shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_init_shell.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_init_shell.c -o CMakeFiles/ush.dir/src/mx_init_shell.c.s

CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o: ../src/mx_is_closed_expression.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_is_closed_expression.c

CMakeFiles/ush.dir/src/mx_is_closed_expression.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_is_closed_expression.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_is_closed_expression.c > CMakeFiles/ush.dir/src/mx_is_closed_expression.c.i

CMakeFiles/ush.dir/src/mx_is_closed_expression.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_is_closed_expression.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_is_closed_expression.c -o CMakeFiles/ush.dir/src/mx_is_closed_expression.c.s

CMakeFiles/ush.dir/src/mx_liststr_delete.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_liststr_delete.c.o: ../src/mx_liststr_delete.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building C object CMakeFiles/ush.dir/src/mx_liststr_delete.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_liststr_delete.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_liststr_delete.c

CMakeFiles/ush.dir/src/mx_liststr_delete.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_liststr_delete.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_liststr_delete.c > CMakeFiles/ush.dir/src/mx_liststr_delete.c.i

CMakeFiles/ush.dir/src/mx_liststr_delete.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_liststr_delete.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_liststr_delete.c -o CMakeFiles/ush.dir/src/mx_liststr_delete.c.s

CMakeFiles/ush.dir/src/mx_liststr_init.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_liststr_init.c.o: ../src/mx_liststr_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building C object CMakeFiles/ush.dir/src/mx_liststr_init.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_liststr_init.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_liststr_init.c

CMakeFiles/ush.dir/src/mx_liststr_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_liststr_init.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_liststr_init.c > CMakeFiles/ush.dir/src/mx_liststr_init.c.i

CMakeFiles/ush.dir/src/mx_liststr_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_liststr_init.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_liststr_init.c -o CMakeFiles/ush.dir/src/mx_liststr_init.c.s

CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o: ../src/mx_liststr_pop_front.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building C object CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_liststr_pop_front.c

CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_liststr_pop_front.c > CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.i

CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_liststr_pop_front.c -o CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.s

CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o: ../src/mx_liststr_push_front.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building C object CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_liststr_push_front.c

CMakeFiles/ush.dir/src/mx_liststr_push_front.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_liststr_push_front.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_liststr_push_front.c > CMakeFiles/ush.dir/src/mx_liststr_push_front.c.i

CMakeFiles/ush.dir/src/mx_liststr_push_front.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_liststr_push_front.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_liststr_push_front.c -o CMakeFiles/ush.dir/src/mx_liststr_push_front.c.s

CMakeFiles/ush.dir/src/mx_new_global_env.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_new_global_env.c.o: ../src/mx_new_global_env.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Building C object CMakeFiles/ush.dir/src/mx_new_global_env.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_new_global_env.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_new_global_env.c

CMakeFiles/ush.dir/src/mx_new_global_env.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_new_global_env.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_new_global_env.c > CMakeFiles/ush.dir/src/mx_new_global_env.c.i

CMakeFiles/ush.dir/src/mx_new_global_env.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_new_global_env.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_new_global_env.c -o CMakeFiles/ush.dir/src/mx_new_global_env.c.s

CMakeFiles/ush.dir/src/mx_output.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_output.c.o: ../src/mx_output.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_23) "Building C object CMakeFiles/ush.dir/src/mx_output.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_output.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_output.c

CMakeFiles/ush.dir/src/mx_output.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_output.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_output.c > CMakeFiles/ush.dir/src/mx_output.c.i

CMakeFiles/ush.dir/src/mx_output.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_output.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_output.c -o CMakeFiles/ush.dir/src/mx_output.c.s

CMakeFiles/ush.dir/src/mx_print_prompt.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_print_prompt.c.o: ../src/mx_print_prompt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_24) "Building C object CMakeFiles/ush.dir/src/mx_print_prompt.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_print_prompt.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_print_prompt.c

CMakeFiles/ush.dir/src/mx_print_prompt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_print_prompt.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_print_prompt.c > CMakeFiles/ush.dir/src/mx_print_prompt.c.i

CMakeFiles/ush.dir/src/mx_print_prompt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_print_prompt.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_print_prompt.c -o CMakeFiles/ush.dir/src/mx_print_prompt.c.s

CMakeFiles/ush.dir/src/mx_read_input.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_read_input.c.o: ../src/mx_read_input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_25) "Building C object CMakeFiles/ush.dir/src/mx_read_input.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_read_input.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_read_input.c

CMakeFiles/ush.dir/src/mx_read_input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_read_input.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_read_input.c > CMakeFiles/ush.dir/src/mx_read_input.c.i

CMakeFiles/ush.dir/src/mx_read_input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_read_input.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_read_input.c -o CMakeFiles/ush.dir/src/mx_read_input.c.s

CMakeFiles/ush.dir/src/mx_sort_arr.c.o: CMakeFiles/ush.dir/flags.make
CMakeFiles/ush.dir/src/mx_sort_arr.c.o: ../src/mx_sort_arr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_26) "Building C object CMakeFiles/ush.dir/src/mx_sort_arr.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ush.dir/src/mx_sort_arr.c.o   -c /Users/ihumeniuk/Desktop/work/src/mx_sort_arr.c

CMakeFiles/ush.dir/src/mx_sort_arr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ush.dir/src/mx_sort_arr.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ihumeniuk/Desktop/work/src/mx_sort_arr.c > CMakeFiles/ush.dir/src/mx_sort_arr.c.i

CMakeFiles/ush.dir/src/mx_sort_arr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ush.dir/src/mx_sort_arr.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ihumeniuk/Desktop/work/src/mx_sort_arr.c -o CMakeFiles/ush.dir/src/mx_sort_arr.c.s

# Object files for target ush
ush_OBJECTS = \
"CMakeFiles/ush.dir/src/main.c.o" \
"CMakeFiles/ush.dir/src/mx_builtin_cd.c.o" \
"CMakeFiles/ush.dir/src/mx_builtin_echo.c.o" \
"CMakeFiles/ush.dir/src/mx_builtin_export.c.o" \
"CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o" \
"CMakeFiles/ush.dir/src/mx_builtins.c.o" \
"CMakeFiles/ush.dir/src/mx_check_buffer.c.o" \
"CMakeFiles/ush.dir/src/mx_driver_loop.c.o" \
"CMakeFiles/ush.dir/src/mx_env_delete.c.o" \
"CMakeFiles/ush.dir/src/mx_env_get_value.c.o" \
"CMakeFiles/ush.dir/src/mx_env_init.c.o" \
"CMakeFiles/ush.dir/src/mx_env_set_var.c.o" \
"CMakeFiles/ush.dir/src/mx_eval.c.o" \
"CMakeFiles/ush.dir/src/mx_free_all.c.o" \
"CMakeFiles/ush.dir/src/mx_history.c.o" \
"CMakeFiles/ush.dir/src/mx_init_shell.c.o" \
"CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o" \
"CMakeFiles/ush.dir/src/mx_liststr_delete.c.o" \
"CMakeFiles/ush.dir/src/mx_liststr_init.c.o" \
"CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o" \
"CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o" \
"CMakeFiles/ush.dir/src/mx_new_global_env.c.o" \
"CMakeFiles/ush.dir/src/mx_output.c.o" \
"CMakeFiles/ush.dir/src/mx_print_prompt.c.o" \
"CMakeFiles/ush.dir/src/mx_read_input.c.o" \
"CMakeFiles/ush.dir/src/mx_sort_arr.c.o"

# External object files for target ush
ush_EXTERNAL_OBJECTS =

ush: CMakeFiles/ush.dir/src/main.c.o
ush: CMakeFiles/ush.dir/src/mx_builtin_cd.c.o
ush: CMakeFiles/ush.dir/src/mx_builtin_echo.c.o
ush: CMakeFiles/ush.dir/src/mx_builtin_export.c.o
ush: CMakeFiles/ush.dir/src/mx_builtin_pwd.c.o
ush: CMakeFiles/ush.dir/src/mx_builtins.c.o
ush: CMakeFiles/ush.dir/src/mx_check_buffer.c.o
ush: CMakeFiles/ush.dir/src/mx_driver_loop.c.o
ush: CMakeFiles/ush.dir/src/mx_env_delete.c.o
ush: CMakeFiles/ush.dir/src/mx_env_get_value.c.o
ush: CMakeFiles/ush.dir/src/mx_env_init.c.o
ush: CMakeFiles/ush.dir/src/mx_env_set_var.c.o
ush: CMakeFiles/ush.dir/src/mx_eval.c.o
ush: CMakeFiles/ush.dir/src/mx_free_all.c.o
ush: CMakeFiles/ush.dir/src/mx_history.c.o
ush: CMakeFiles/ush.dir/src/mx_init_shell.c.o
ush: CMakeFiles/ush.dir/src/mx_is_closed_expression.c.o
ush: CMakeFiles/ush.dir/src/mx_liststr_delete.c.o
ush: CMakeFiles/ush.dir/src/mx_liststr_init.c.o
ush: CMakeFiles/ush.dir/src/mx_liststr_pop_front.c.o
ush: CMakeFiles/ush.dir/src/mx_liststr_push_front.c.o
ush: CMakeFiles/ush.dir/src/mx_new_global_env.c.o
ush: CMakeFiles/ush.dir/src/mx_output.c.o
ush: CMakeFiles/ush.dir/src/mx_print_prompt.c.o
ush: CMakeFiles/ush.dir/src/mx_read_input.c.o
ush: CMakeFiles/ush.dir/src/mx_sort_arr.c.o
ush: CMakeFiles/ush.dir/build.make
ush: libmx.a
ush: CMakeFiles/ush.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_27) "Linking C executable ush"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ush.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ush.dir/build: ush

.PHONY : CMakeFiles/ush.dir/build

CMakeFiles/ush.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ush.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ush.dir/clean

CMakeFiles/ush.dir/depend:
	cd /Users/ihumeniuk/Desktop/work/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ihumeniuk/Desktop/work /Users/ihumeniuk/Desktop/work /Users/ihumeniuk/Desktop/work/cmake-build-debug /Users/ihumeniuk/Desktop/work/cmake-build-debug /Users/ihumeniuk/Desktop/work/cmake-build-debug/CMakeFiles/ush.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ush.dir/depend
