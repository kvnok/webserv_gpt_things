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

// void executeCGI(int client_fd, const std::string& path, const std::string& query_string) {
//     // For demonstration, let's assume we execute a CGI script and send its output as response
//     // You should replace this with actual CGI execution code based on the file extension
//     std::stringstream response;
//     response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
//     response << "Executing CGI script: " << path << " with query string: " << query_string;
//     std::string response_str = response.str();
//     send(client_fd, response_str.c_str(), response_str.length(), 0);
// }

// void handleRequest(int client_fd, const std::string& method, const std::string& path, const std::string& query_string, const std::string& body) {
//     // Check if the requested path corresponds to a CGI script based on file extension
//     // For demonstration, assume ".cgi" extension triggers CGI execution
//     if (path.length() >= 4 && path.substr(path.length() - 4) == ".cgi") {
//         executeCGI(client_fd, path, query_string);
//     } else {
//         // For demonstration, handle other requests as static file serving
//         serveStaticFile(client_fd, path);
//     }
// }

// int main() {
//     // Server setup code...

//     while (true) {
//         // Polling loop...

//         // Handle client activity
//         for (size_t i = 1; i < fds.size(); ++i) {
//             if (fds[i].revents & POLLIN) {
//                 // For demonstration, assume request format: "METHOD /path?query_string HTTP/1.1\r\n\r\n[body]"
//                 std::string request(buffer);
//                 std::istringstream iss(request);
//                 std::string request_line;
//                 std::getline(iss, request_line);
//                 std::istringstream iss_line(request_line);
//                 std::string method, path, protocol;
//                 iss_line >> method >> path >> protocol;

//                 // Extract query string from path
//                 size_t query_pos = path.find('?');
//                 std::string query_string;
//                 if (query_pos != std::string::npos) {
//                     query_string = path.substr(query_pos + 1);
//                     path = path.substr(0, query_pos);
//                 }

//                 // Extract request body (if present)
//                 std::string body;
//                 std::getline(iss, body, '\0');

//                 // Handle the request
//                 handleRequest(fds[i].fd, method, path, query_string, body);

//                 fds.erase(fds.begin() + i);
//                 --i; // Adjust loop index after erasing element
//             }
//         }
//     }

//     // Server cleanup code...
// }

int main() {
    
}