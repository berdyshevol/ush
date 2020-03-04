//
// Created by Oleg Berdyshev on 2/27/20.
//
#include "ush.h"

// ---------------------- API

int *mx_pipe_fd_new() {
    int *pipe_fd = malloc(3 * sizeof (int));
    pipe_fd[0] = -1;
    pipe_fd[1] = -1;
    pipe_fd[2] = -1;
//    pipe_fd[3] = 1;
    return pipe_fd;
}

// free and close
//void mx_pipe_fd_delete(int **pipe_fd) {
//    if (pipe_fd != NULL && *pipe_fd != NULL) {
//        if (mx_fd_is_valid((*pipe_fd)[0]))
//            mx_smart_close_fd(&(*pipe_fd)[0], 0);
//        if (mx_fd_is_valid((*pipe_fd)[1]))
//            mx_smart_close_fd(&(*pipe_fd)[1], 1);
//        if (mx_fd_is_valid((*pipe_fd)[2]))
//            mx_smart_close_fd(&(*pipe_fd)[2], 0);
//        if (mx_fd_is_valid((*pipe_fd)[3]))
//            mx_smart_close_fd(&(*pipe_fd)[3], 1);
//        free(*pipe_fd);
//        *pipe_fd = NULL;
//    }
//}
void mx_pipe_fd_delete(int **pipe_fd) {
    if (pipe_fd != NULL && *pipe_fd != NULL) {
//        if (mx_fd_is_valid((*pipe_fd)[0]))
//            mx_smart_close_fd(&(*pipe_fd)[0], 0);
//        if (mx_fd_is_valid((*pipe_fd)[1]))
//            mx_smart_close_fd(&(*pipe_fd)[1], 1);
//        if (mx_fd_is_valid((*pipe_fd)[2]))
//            mx_smart_close_fd(&(*pipe_fd)[2], 0);
//        if (mx_fd_is_valid((*pipe_fd)[3]))
//            mx_smart_close_fd(&(*pipe_fd)[3], 1);
        free(*pipe_fd);
        *pipe_fd = NULL;
    }
}

void mx_smart_close_fd(int *fd, int std) {
    if (*fd != std) {
        close(*fd);
        *fd = -1;
    }
}

int mx_fd_is_valid(int fd) {
    if (fcntl(fd, F_GETFD) == FD_CLOEXEC)
        return false;
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void mx_reset_pipefd(int *pipe_fd) {
    if (pipe_fd == NULL)
        return;
    if (pipe_fd[2] != 0) {
        dup2(pipe_fd[2], 0);
        mx_smart_close_fd(&pipe_fd[2], 0);
    }
    if (pipe_fd[3] != 1) {
        dup2(pipe_fd[3], 1);
        mx_smart_close_fd(&pipe_fd[3], 1);
    }
}

//bool mx_has_pipe(int *pipe_fd) {
//    bool res = false;
//    if (pipe_fd == NULL)
//        return res;
//    if (pipe_fd[0] != 0) {
//        res = true;
//    }
//    if (pipe_fd[1] != 1) {
//        res = true;
//    }
//    return res;
//}

bool mx_has_pipe(int *pipe_fd) {
    bool res = false;
    if (pipe_fd == NULL)
        return res;
    if (pipe_fd[0] != -1) {
        res = true;
    }
    return res;
}

//bool  mx_apply_pipe(int *pipe_fd) {
//    bool res = false;
//    if (pipe_fd == NULL)
//        return res;
//    if (pipe_fd[0] != 0) {
//        pipe_fd[2] = dup(pipe_fd[0]);
//        dup2(pipe_fd[0], 0);
//        close(pipe_fd[0]);
//        res = true;
//    }
//    if (pipe_fd[1] != 1) {
//        pipe_fd[3] = dup(pipe_fd[1]);
//        dup2(pipe_fd[1], 1);  // !!!!!!!!!!!!!!!!
//        close(pipe_fd[1]);
//        res = true;
//    }
//    return res;
//}
bool  mx_apply_pipe(int *pipe_fd) {
    bool res = false;
    if (pipe_fd == NULL)
        return res;
    if (pipe_fd[1] != 0 || pipe_fd[1] != 1) {
        dup2(pipe_fd[0], pipe_fd[1]);
        close(pipe_fd[0]);
        res = true;
    }
    return res;
}

//// test void mx_pipe_fd_delete(int **pipe_fd) {
//#include <assert.h>
//int main(void) {
//    int fd = open("test", O_WRONLY|O_CREAT|O_TRUNC, 0666);
//    int fd1 = open("test1", O_WRONLY|O_CREAT|O_TRUNC, 0666);
//
//    assert(mx_fd_is_valid(fd) == true);
//    assert(mx_fd_is_valid(fd1) == true);
//    assert(mx_fd_is_valid(0) == true);
//    assert(mx_fd_is_valid(1) == true);
//    assert(mx_fd_is_valid(2) == true);
//    assert(mx_fd_is_valid(fd+100) == false);
//    assert(mx_fd_is_valid(fd1+100) == false);
//    close(fd);
//    close(fd1);
//    assert(mx_fd_is_valid(fd) == false);
//    assert(mx_fd_is_valid(fd1) == false);
//
//    int *pipe_fd = mx_pipe_fd_new();
//    assert(mx_fd_is_valid(pipe_fd[0]) == true);
//    assert(mx_fd_is_valid(pipe_fd[1]) == true);
//    mx_pipe_fd_delete(&pipe_fd);
//    assert(pipe_fd == NULL);
//
//
//    printf("\nSUCCESS\n----\n");
//    system("leaks -q ush");
//    return 0;
//}

