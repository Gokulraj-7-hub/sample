#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("child process, pid = %d\n", getpid());
        exit(0);  // Simulate successful execution
    } else {
        // Parent process
        printf("parent process, pid = %d\n", getpid());

        if (waitpid(pid, &status, 0) > 0) {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                printf("Program execution successful\n");
            } else {
                printf("Child process exited with error\n");
            }
        } else {
            perror("waitpid failed");
        }
    }

    return 0;
}
