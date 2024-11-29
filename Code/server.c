#include "http_server.h"

// Starts the HTTP server
void start_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address and bind the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(PORT);      // Convert port to network byte order

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server running on port %d\n", PORT);

    // Accept and handle client connections in a loop
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE];
        int bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0); // Read the request
        buffer[bytes_read] = '\0'; // Null-terminate the request string

        printf("Request:\n%s\n", buffer);
        process_request(client_socket, buffer); // Process the request

        close(client_socket); // Close the connection after handling
    }

    close(server_socket); // Close the server socket when shutting down
}

int main() {
    start_server(); // Start the HTTP server
    return 0;
}

