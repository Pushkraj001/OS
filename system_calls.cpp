#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // Process-related system calls
    pid_t child_pid;
    int status;

    printf("Parent process (PID: %d)\n", getpid());

    // Forking a child process
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork"); // Print error message if fork fails
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        exit(EXIT_SUCCESS); // Exit child process
    } else {
        // Parent process
        printf("Parent process waiting for child process to finish...\n");
        // Waiting for the child process to finish
        wait(&status);
        printf("Child process has finished\n");
    }

    // File-related system calls
    int fd;
    ssize_t bytes_read, bytes_written;
    char buffer[100];

    // Creating or truncating a file for writing
    fd = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open"); // Print error message if open fails
        exit(EXIT_FAILURE);
    }

    // Writing data to the file
    bytes_written = write(fd, "Hello, world!\n", 14);
    if (bytes_written == -1) {
        perror("write"); // Print error message if write fails
        exit(EXIT_FAILURE);
    }
    close(fd); // Close the file descriptor

    // Opening the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open"); // Print error message if open fails
        exit(EXIT_FAILURE);
    }

    // Reading data from the file
    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read"); // Print error message if read fails
        exit(EXIT_FAILURE);
    }
    close(fd); // Close the file descriptor

    printf("Read from file: %s", buffer);

    // Protection-related system call
    // Changing file permissions
    if (chmod("example.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("chmod"); // Print error message if chmod fails
        exit(EXIT_FAILURE);
    }

    printf("File permissions changed successfully\n");

    return 0;
}
