
 #include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // for open()
#include <unistd.h>   // for read(), write(), close()
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open source file (result.txt) in read-only mode
    source_fd = open("result.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening result.txt");
        exit(1);
    }

    // Open destination file (copyresult.txt) in write mode, create if not exists
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening/creating copyresult.txt");
        close(source_fd);
        exit(1);
    }

    // Copy loop
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to copyresult.txt");
            close(source_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read < 0) {
        perror("Error reading result.txt");
    }

    // Close files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully from result.txt to copyresult.txt\n");
    return 0;
}

