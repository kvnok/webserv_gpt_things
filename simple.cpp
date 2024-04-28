#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;
const int BACKLOG = 10;
const int BUFFER_SIZE = 1024;

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        std::cerr << "Error receiving data from client\n";
        return;
    }

    // Parse HTTP request (very basic parsing)
    std::string request(buffer, bytes_received);
    std::cout << "Received request:\n" << request << std::endl;

    // Generate HTTP response (very basic response)
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    ssize_t bytes_sent = send(client_socket, response.c_str(), response.size(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Error sending response to client\n";
    }

    // Close client socket
    close(client_socket);
}

int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
        return 1;
    }

    // Bind socket to port
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(server_socket, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
        close(server_socket);
        return 1;
    }

    // Listen for connections
    if (listen(server_socket, BACKLOG) == -1) {
        std::cerr << "Error listening on socket: " << strerror(errno) << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Server started. Listening on port " << PORT << std::endl;

    // Accept connections and handle requests
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len);
        if (client_socket == -1) {
            std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
            continue;
        }

        // Fork a child process to handle the request
        pid_t pid = fork();
        if (pid == -1) {
            std::cerr << "Error forking process: " << strerror(errno) << std::endl;
            close(client_socket);
            continue;
        } else if (pid == 0) {
            // Child process
            close(server_socket); // Close the server socket in the child process
            handle_request(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket); // Close the client socket in the parent process
        }
    }

    // Close server socket (never reached in this example)
    close(server_socket);
    return 0;
}
/*
cc simple.cpp -o ok -lstdc++
./ok
cc simple.cpp -o ok && ./ok
*/
