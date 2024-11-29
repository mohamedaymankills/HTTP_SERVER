#include "http_server.h"

// Processes an incoming HTTP request and routes it to the appropriate handler
void process_request(int client_socket, const char *request) {
    char method[16], path[256];
    sscanf(request, "%s %s", method, path); // Parse the method (e.g., GET) and resource path

    if (strcmp(method, "GET") != 0) { // Only GET method is supported
        send_404(client_socket);      // Send 404 for unsupported methods
        return;
    }

    // Remove leading slash from the resource path
    char *resource = path + 1;
    if (strcmp(resource, "") == 0) resource = "."; // Default to current directory

    struct stat st;
    if (stat(resource, &st) == 0) { // Check the type of the resource
        if (S_ISDIR(st.st_mode)) {
            list_directory(client_socket, resource); // List directory contents
        } else if (S_ISREG(st.st_mode)) {
            if (strstr(resource, ".cgi")) {
                execute_cgi(client_socket, resource); // Execute CGI scripts
            } else {
                serve_file(client_socket, resource); // Serve regular files
            }
        } else {
            send_404(client_socket); // Unsupported file types
        }
    } else {
        send_404(client_socket); // Resource does not exist
    }
}

