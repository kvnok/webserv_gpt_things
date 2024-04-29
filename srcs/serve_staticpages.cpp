#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// Function to serve static files
void serveStaticFile(int client_fd, const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        // File not found, send 404 response
        const char* http_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><p>The requested URL was not found on this server.</p></body></html>\r\n";
        send(client_fd, http_response, strlen(http_response), 0);
        return;
    }

    // File found, determine its size
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read file contents into buffer
    std::vector<char> buffer(file_size);
    if (!file.read(buffer.data(), file_size)) {
        // Error reading file, send 500 response
        const char* http_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>500 Internal Server Error</title></head><body><h1>500 Internal Server Error</h1><p>An internal server error occurred while processing the request.</p></body></html>\r\n";
        send(client_fd, http_response, strlen(http_response), 0);
        return;
    }

    // Send HTTP response with file contents
    std::string http_response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(file_size) + "\r\n\r\n";
    send(client_fd, http_response.c_str(), http_response.length(), 0);
    send(client_fd, buffer.data(), buffer.size(), 0);
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
    if (listen(server_fd, MAX_CLIENTS) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    std::vector<pollfd> fds(1, {server_fd, POLLIN});

    while (true) {
        int activity = poll(fds.data(), fds.size(), -1);
        if (activity == -1) {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        if (fds[0].revents & POLLIN) {
            // New incoming connection
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) == -1) {
                perror("accept failed");
                continue;
            }
            std::cout << "New connection accepted" << std::endl;
            fds.push_back({new_socket, POLLIN});
        }

        // Handle client activity
        for (size_t i = 1; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                // For demonstration, serve index.html for all requests
                serveStaticFile(fds[i].fd, "index.html");
                fds.erase(fds.begin() + i);
                --i; // Adjust loop index after erasing element
            }
        }
    }

    close(server_fd);
    return 0;
}
