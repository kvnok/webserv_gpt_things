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
#include <unordered_map>

#define BUFFER_SIZE 1024

// Structure to hold information about a listening socket
struct ListeningSocket {
    int socket_fd;
    struct sockaddr_in address;
};

// Function to create and bind a listening socket
int createListeningSocket(int port) {
    int socket_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Create socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(socket_fd, SOMAXCONN) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    return socket_fd;
}

int main() {
    // Example configuration settings (port numbers)
    std::unordered_map<int, std::string> portConfigurations = {
        {8080, "config1.conf"},
        {9090, "config2.conf"}
    };

    std::vector<ListeningSocket> listeningSockets;

    // Create and bind listening sockets based on configuration
    for (const auto& pair : portConfigurations) {
        int port = pair.first;
        int socket_fd = createListeningSocket(port);
        std::cout << "Listening on port " << port << std::endl;

        // Store listening socket information
        ListeningSocket listeningSocket;
        listeningSocket.socket_fd = socket_fd;
        listeningSocket.address.sin_port = htons(port);
        listeningSockets.push_back(listeningSocket);
    }

    // Polling loop for handling incoming connections
    std::vector<pollfd> fds(listeningSockets.size());
    for (size_t i = 0; i < listeningSockets.size(); ++i) {
        fds[i].fd = listeningSockets[i].socket_fd;
        fds[i].events = POLLIN;
    }

    while (true) {
        int activity = poll(fds.data(), fds.size(), -1);
        if (activity == -1) {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        // Handle incoming connections
        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                struct sockaddr_in client_address;
                int addrlen = sizeof(client_address);
                int new_socket;

                if ((new_socket = accept(fds[i].fd, (struct sockaddr *)&client_address, (socklen_t*)&addrlen)) == -1) {
                    perror("accept failed");
                    continue;
                }

                // Process incoming connection
                std::cout << "New connection accepted on port " << ntohs(listeningSockets[i].address.sin_port) << std::endl;

                // Implement request handling for the new connection
                // For demonstration, let's just close the connection
                close(new_socket);
            }
        }
    }

    // Close listening sockets
    for (const auto& listeningSocket : listeningSockets) {
        close(listeningSocket.socket_fd);
    }

    return 0;
}
