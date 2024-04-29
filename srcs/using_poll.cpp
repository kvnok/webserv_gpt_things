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

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void handleClient(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    int bytesReceived = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytesReceived <= 0) {
        // Handle connection closed or error
        close(client_fd);
        return;
    }

    // Process request, send response, etc.
    // For demonstration, let's just print the received data
    std::cout << "Received message from client: " << buffer << std::endl;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

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
                handleClient(fds[i].fd);
                fds.erase(fds.begin() + i);
                --i; // Adjust loop index after erasing element
            }
        }
    }

    close(server_fd);
    return 0;
}
