#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src_fd, dest_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // 1. Open source file (read-only)
    src_fd = open("result.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening result.txt");
        return 1;
    }

    // 2. Open/Create destination file (write-only, create if missing, clear if exists)
    // 0644 gives read/write permissions to the owner
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error creating copyresult.txt");
        close(src_fd);
        return 1;
    }

    // 3. Read from source and write to destination
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error during writing");
            break;
        }
    }

    // 4. Close both files
    close(src_fd);
    close(dest_fd);

    printf("File copied successfully via system calls.\n");
    return 0;
}
