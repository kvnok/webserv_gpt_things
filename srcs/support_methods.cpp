// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <cstdlib>
// #include <cstdio>
// #include <unistd.h>
// #include <errno.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <poll.h>
// #include <fstream>
// #include <sstream>
// #include <unordered_map>

// #define PORT 8080
// #define MAX_CLIENTS 10
// #define BUFFER_SIZE 1024

// void handleGET(int client_fd, const std::string& path) {
//     // For demonstration, let's assume we serve a static file for GET requests
//     serveStaticFile(client_fd, path);
// }

// void handlePOST(int client_fd, const std::string& path, const std::string& body) {
//     // For demonstration, let's assume we handle POST data and send a response
//     std::stringstream response;
//     response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
//     response << "Received POST data: " << body;
//     std::string response_str = response.str();
//     send(client_fd, response_str.c_str(), response_str.length(), 0);
// }

// void handleDELETE(int client_fd, const std::string& path) {
//     // For demonstration, let's assume we delete a resource and send a response
//     std::stringstream response;
//     response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
//     response << "Deleted resource at: " << path;
//     std::string response_str = response.str();
//     send(client_fd, response_str.c_str(), response_str.length(), 0);
// }

// void handleRequest(int client_fd, const std::string& method, const std::string& path, const std::string& body) {
//     if (method == "GET") {
//         handleGET(client_fd, path);
//     } else if (method == "POST") {
//         handlePOST(client_fd, path, body);
//     } else if (method == "DELETE") {
//         handleDELETE(client_fd, path);
//     } else {
//         // Unsupported method, send 405 Method Not Allowed response
//         const char* http_response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>405 Method Not Allowed</title></head><body><h1>405 Method Not Allowed</h1><p>The requested method is not supported for this resource.</p></body></html>\r\n";
//         send(client_fd, http_response, strlen(http_response), 0);
//     }
// }

// int main() {
//     // Server setup code...

//     while (true) {
//         // Polling loop...

//         // Handle client activity
//         for (size_t i = 1; i < fds.size(); ++i) {
//             if (fds[i].revents & POLLIN) {
//                 // For demonstration, assume request format: "METHOD /path HTTP/1.1\r\n\r\n[body]"
//                 std::string request(buffer);
//                 std::istringstream iss(request);
//                 std::string request_line;
//                 std::getline(iss, request_line);
//                 std::istringstream iss_line(request_line);
//                 std::string method, path, protocol;
//                 iss_line >> method >> path >> protocol;

//                 // Extract request body (if present)
//                 std::string body;
//                 std::getline(iss, body, '\0');

//                 // Handle the request based on the method
//                 handleRequest(fds[i].fd, method, path, body);

//                 fds.erase(fds.begin() + i);
//                 --i; // Adjust loop index after erasing element
//             }
//         }
//     }

//     // Server cleanup code...
// }
int main() {
    
}