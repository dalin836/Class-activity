#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create child process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: execute "ls"
        printf("Child process running 'ls'...\n");
        execlp("ls", "ls", NULL);

        // If exec fails
        perror("exec failed");
        exit(1);
    } else {
        // Parent process: wait for child
        wait(NULL);
        printf("Parent process: child finished.\n");
    }

    return 0;
}
