#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("Pipe Error");
        exit(1);
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(pipe1[1]);
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);

        close(pipe2[0]);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);

        char *args[] = {"./first_child", NULL};
        execve("./first_child", args, NULL);
        perror("Error first_child");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe2[1]);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);

        close(pipe3[0]);
        dup2(pipe3[1], STDOUT_FILENO);
        close(pipe3[1]);

        char *args[] = {"./second_child", NULL};
        execve("./second_child", args, NULL);
        perror("Error second_child");
        exit(1);
    }

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[1]);

    char input[BUFFER_SIZE];
    printf("Введите строку: ");
    fgets(input, BUFFER_SIZE, stdin);

    write(pipe1[1], input, strlen(input) + 1);
    close(pipe1[1]);

    char result[BUFFER_SIZE];
    ssize_t n = read(pipe3[0], result, BUFFER_SIZE);
    result[n] = '\0';
    close(pipe3[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Ответ: %s", result);

    return 0;
}
