#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process uses exec() to run `echo` and `seq` to print 0–7
        char *args[] = {"/usr/bin/seq", "0", "7", NULL};
        execv("/usr/bin/seq", args);

        // If exec fails
        perror("execv failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        wait(&status);
        printf("Child is reaped\n");
    }

    return 0;
}
