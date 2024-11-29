
# **HTTP Server in C**

This project is a custom HTTP server implemented in C, designed to handle HTTP requests, serve HTML content, and simulate basic web server functionality. It demonstrates fundamental concepts in socket programming, HTTP protocol handling, and file system interaction.

---

## **Table of Contents**
1. [Introduction](#introduction)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Directory Structure](#directory-structure)
5. [Compilation and Execution](#compilation-and-execution)
6. [How It Works](#how-it-works)
7. [Testing the Server](#testing-the-server)
8. [Limitations](#limitations)
9. [Future Enhancements](#future-enhancements)
10. [License](#license)

---

## **Introduction**

This project implements a basic HTTP server capable of handling requests from a web browser or command-line HTTP clients (e.g., `curl`). It showcases the ability to:
- Serve an introductory page.
- List the contents of directories.
- Display the content of text files.
- Handle invalid requests with appropriate error responses.

---

## **Features**

1. **Serve Static Content:**
   - Provides an introductory page with a bold **Welcome** message when the root (`/`) is accessed.

2. **Directory Browsing:**
   - Lists the contents of a directory if the requested path corresponds to a directory.

3. **File Serving:**
   - Displays the content of a regular text file.

4. **Error Handling:**
   - Responds with appropriate HTTP error messages if:
     - The requested resource does not exist.
     - The request is invalid or malformed.

5. **Simple and Lightweight:**
   - A minimal implementation using only C standard libraries.

---

## **Requirements**

### **Hardware**
- Two laptops (or devices) connected via an Ethernet cable or operating within the same network.

### **Software**
- Linux-based operating system (Ubuntu or similar).
- GCC compiler for building the project.
- Curl (for command-line testing) or a web browser for accessing the server.

---

## **Directory Structure**

The project structure is as follows:

```
project/
├── http_server.c       # Main server code
├── README.md           # Project documentation
└── test_files/         # Sample files and directories for testing
    ├── file1.txt
    ├── file2.txt
    └── subdir/
        └── nested_file.txt
```

---

## **Compilation and Execution**

### **Step 1: Compile the Server**
Run the following command on the server laptop:
```bash
gcc -o http_server http_server.c
```

### **Step 2: Start the Server**
Start the server on the server laptop:
```bash
./http_server
```

The server will start listening on port **8080**.

### **Step 3: Connect to the Server**
- From the client laptop, use a web browser or `curl` to access the server:
  ```bash
  curl http://<server-ip>:8080/
  ```

---

## **How It Works**

1. **Socket Creation and Binding:**
   - The server creates a TCP socket, binds it to port 8080, and listens for incoming client connections.

2. **Request Handling:**
   - Upon receiving a connection, the server reads the client's HTTP request and parses it.

3. **Response Construction:**
   - If the requested resource is:
     - `/`: Sends a homepage with a **Welcome** message.
     - A directory: Sends an HTML response listing the directory's contents.
     - A file: Reads and sends the file's content.
     - Non-existent: Sends a `404 Not Found` error.

4. **Connection Management:**
   - After sending the response, the server closes the client connection and waits for the next request.

---

## **Testing the Server**

### **Step 1: Verify Server Setup**
Ensure the server laptop's IP address is configured correctly (e.g., `192.168.1.1`) and reachable from the client laptop.

### **Step 2: Test with Curl**
Run the following commands on the client laptop:
- Access the homepage:
  ```bash
  curl http://192.168.1.1:8080/
  ```
- Test a directory listing:
  ```bash
  curl http://192.168.1.1:8080/test_files/
  ```
- Test file content:
  ```bash
  curl http://192.168.1.1:8080/test_files/file1.txt
  ```
- Test a non-existent resource:
  ```bash
  curl http://192.168.1.1:8080/nonexistent
  ```

### **Step 3: Test with a Browser**
Open a web browser on the client laptop and navigate to:
```
http://192.168.1.1:8080/
```

---

## **Limitations**

1. **No HTTPS Support:**
   - The server only supports plain HTTP over TCP and does not implement SSL/TLS.

2. **Limited MIME Type Handling:**
   - The server does not differentiate file types or set MIME types dynamically.

3. **Single-Threaded:**
   - The server handles one connection at a time, which may lead to delays under multiple simultaneous requests.

4. **File Size Limits:**
   - Large files may exceed buffer sizes, causing partial responses.

---

## **Future Enhancements**

1. **Multithreading:**
   - Implement threading to handle multiple client connections simultaneously.

2. **Dynamic Content:**
   - Add support for executing CGI scripts or serving dynamic content.

3. **MIME Type Support:**
   - Implement logic to set appropriate MIME types for various file extensions.

4. **Logging:**
   - Add a logging mechanism to track requests and server activity.

5. **Security:**
   - Add HTTPS support using libraries like OpenSSL.

6. **Error Pages:**
   - Customize error pages with detailed explanations and links.

---

## **License**

This project is licensed under the MIT License. You are free to use, modify, and distribute the code with proper attribution.

---

Feel free to reach out if you need additional help or explanations for specific parts of the project!
