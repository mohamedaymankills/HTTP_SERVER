#include "http_server.h"

// Sends an HTML list of directory contents as the response
void list_directory(int client_socket, const char *path) {
    char body[BUFFER_SIZE] = "<ul>"; // HTML unordered list start tag
    DIR *dir = opendir(path);       // Open the directory specified by the path
    if (dir) {
        struct dirent *entry;
        // Read directory entries one by one
        while ((entry = readdir(dir)) != NULL) {
            // Add each entry as a list item with a hyperlink
            strcat(body, "<li><a href=\"");
            strcat(body, entry->d_name); // Hyperlink points to the entry name
            strcat(body, "\">");
            strcat(body, entry->d_name); // Display the entry name
            strcat(body, "</a></li>");
        }
        closedir(dir); // Close the directory after reading
    }
    strcat(body, "</ul>"); // HTML unordered list end tag
    send_response(client_socket, 200, "text/html", body); // Send the list as an HTTP response
}

// Sends the contents of a file to the client as plain text
void serve_file(int client_socket, const char *path) {
    int fd = open(path, O_RDONLY); // Open the file in read-only mode
    if (fd < 0) {
        send_404(client_socket); // If the file cannot be opened, send a 404 response
        return;
    }

    char body[BUFFER_SIZE];
    int bytes_read = read(fd, body, sizeof(body) - 1); // Read file contents into the buffer
    body[bytes_read] = '\0';                          // Null-terminate the buffer
    close(fd);                                        // Close the file descriptor

    send_response(client_socket, 200, "text/plain", body); // Send the file contents as a response
}

// Executes a CGI script and sends its output as an HTML response
void execute_cgi(int client_socket, const char *path) {
    FILE *fp = popen(path, "r"); // Open the script for reading using a pipe
    if (!fp) {
        send_404(client_socket); // If the script cannot be executed, send a 404 response
        return;
    }

    char body[BUFFER_SIZE];
    fread(body, 1, sizeof(body) - 1, fp); // Read the script's output into the buffer
    pclose(fp);                          // Close the pipe after reading

    send_response(client_socket, 200, "text/html", body); // Send the script's output as a response
}

