#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void serve_html(int client_socket, const std::string& request_path) {
    std::string filename = (request_path == "/") ? "index.html" : request_path.substr(1);
    std::ifstream html_file(filename);
    static bool error_printed = false; // Flag to track if error message has been printed

    if (!html_file.is_open()) {
        if (!error_printed) { // Print error message only once per request
            std::cerr << "Error: Unable to open " << filename << std::endl;
            error_printed = true;
        }

        // Send a 404 Not Found response
        std::stringstream response;
        response << "HTTP/1.1 404 Not Found\r\n";
        response << "Content-Type: text/html\r\n";
        response << "\r\n";
        response << "<h1>404 Not Found</h1>";
        std::string response_str = response.str();
        send(client_socket, response_str.c_str(), response_str.length(), 0);
        return;
    }

    // Reset the error_printed flag if the file is found
    error_printed = false;

    // File exists, serve it
    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Connection: keep-alive\r\n"; // Keep the connection alive
    response << "\r\n";
    response << html_file.rdbuf();

    std::string response_str = response.str();
    send(client_socket, response_str.c_str(), response_str.length(), 0);
}



int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) == -1) {
            perror("accept failed");
            continue;
        }

        // Receive HTTP request
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        std::string request(buffer);

        // Parse request path
        std::istringstream iss(request);
        std::string request_line;
        std::getline(iss, request_line);
        std::istringstream iss_line(request_line);
        std::string method, path, protocol;
        iss_line >> method >> path >> protocol;


        // std::cout << method << std::endl;
        // std::cout << path << std::endl;
        // std::cout << protocol << std::endl;
        
        
        // Serve HTML file
        serve_html(new_socket, path);

        // Close the connection
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
/*
c++ -o hi hostindex.cpp && ./hi

https://chat.openai.com/c/7d1c4b14-c152-4eda-9d42-16a0d80f1dbe

netstat -an | grep 8080
*/
