#include "http_server.h"

// Sends an HTTP response to the client with a specified status code, content type, and body
void send_response(int client_socket, int status_code, const char *content_type, const char *body) {
    // Buffers to construct the HTTP response and header
    char response[BUFFER_SIZE];
    char header[BUFFER_SIZE];

    // HTML wrappers for the body content
    char html_start[] =
        "<html>"
        "<head><title>HTTP Server</title></head>"
        "<body>"
        "<b>STMicroelectronics Cairo</b><br><br>"; // Adds a bold welcome message
    char html_end[] = "</body></html>";

    // Construct the HTTP header with status, content type, and length
    sprintf(header,
            "HTTP/1.1 %d OK\r\n"
            "Content-Type: %s\r\n"
            "Content-Length: %ld\r\n"
            "\r\n",
            status_code, content_type, strlen(html_start) + strlen(body) + strlen(html_end));

    // Combine the header and HTML content into the response
    strcpy(response, header);
    strcat(response, html_start);
    strcat(response, body);
    strcat(response, html_end);

    // Send the response to the client
    send(client_socket, response, strlen(response), 0);
}

// Sends a 404 Not Found response when a requested resource is unavailable
void send_404(int client_socket) {
    char body[] = "<h1>404 Not Found</h1>"; // Simple HTML for the error message
    send_response(client_socket, 404, "text/html", body);
}

