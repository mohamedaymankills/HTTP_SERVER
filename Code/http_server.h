#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

// Includes all necessary headers for networking, file handling, and system utilities
#include <stdio.h>      // Standard I/O operations
#include <stdlib.h>     // Memory allocation, process control, and conversions
#include <string.h>     // String manipulation functions
#include <unistd.h>     // POSIX API for close, read, write, etc.
#include <arpa/inet.h>  // Internet operations for sockets
#include <sys/types.h>  // Data types used in system calls
#include <sys/stat.h>   // File status and permission macros
#include <dirent.h>     // Directory operations
#include <fcntl.h>      // File control options

// Server configuration
#define PORT 9090           // The port number the server listens on
#define BUFFER_SIZE 4096    // The size of the buffer used for I/O operations

// Function declarations
// Sends an HTTP response to the client
void send_response(int client_socket, int status_code, const char *content_type, const char *body);

// Sends a 404 Not Found error to the client
void send_404(int client_socket);

// Lists the contents of a directory as an HTML response
void list_directory(int client_socket, const char *path);

// Serves a regular file to the client
void serve_file(int client_socket, const char *path);

// Executes a CGI script and sends the output as an HTTP response
void execute_cgi(int client_socket, const char *path);

// Processes an HTTP request received from the client
void process_request(int client_socket, const char *request);

// Starts the HTTP server
void start_server();

#endif // HTTP_SERVER_H

