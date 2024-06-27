#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

    int keepConnection = 1;
    while (keepConnection) {
        int serverSocket, clientSocket;
        struct sockaddr_in serverAddr, clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        char buffer[BUFFER_SIZE];

        // Create server socket
        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        // Set up server address structure
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(PORT);

        // Bind socket to address and port
        if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }

        // Listen for incoming connections
        if (listen(serverSocket, 5) == -1) {
            perror("Listen failed");
            exit(EXIT_FAILURE);
        }

        printf("Server listening on port %d...\n", PORT);

        // Accept incoming connection
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        // Receive data from client
        ssize_t bytesRead;
        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytesRead] = '\0';  // Null-terminate the received data
            printf("Received data: %s", buffer);
        }

        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        // Close the sockets
        close(clientSocket);
        close(serverSocket);


    }

    return 0;
}
