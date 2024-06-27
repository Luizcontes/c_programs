#include <unistd.h>
#include <stdio.h>

int main() {
    // File descriptor for standard output (stdout)
    int fileDescriptor = 1;

    // String to be written
    const char *message = "Hello, write() function!\n";

    int size_t = 0;
    while(message[size_t] != '\0') {
        size_t++;
    }

    // Using the write() function to write to stdout
    ssize_t bytesWritten = write(fileDescriptor, message, size_t);

    printf("write call returned number: %zd", bytesWritten);

    // Checking for errors
    // if (bytesWritten == -1) {
    //     // Handle error if write() fails
    //     return 1;
    // }

    return 0;
}
