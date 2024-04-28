#include "header.hpp"

// Function implementations
void use_execve() {
    std::cout << "Start of use_execve()" << std::endl;
    // Your code using execve goes here
    // Example:
    const char* argv[] = {"/bin/ls", "-l", NULL};
    // execve(argv[0], argv, NULL);
    std::cout << "End of use_execve()" << std::endl;
}

void use_dup() {
    std::cout << "Start of use_dup()" << std::endl;
    // Your code using dup goes here
    // Example:
    int oldfd = 0; // file descriptor to duplicate
    int newfd = dup(oldfd);
    if (newfd == -1) {
        // handle error
    }
    std::cout << "End of use_dup()" << std::endl;
}

void use_dup2() {
    std::cout << "Start of use_dup2()" << std::endl;
    // Your code using dup2 goes here
    // Example:
    int oldfd = 0; // file descriptor to duplicate
    int newfd = 1; // new file descriptor to use
    if (dup2(oldfd, newfd) == -1) {
        // handle error
    }
    std::cout << "End of use_dup2()" << std::endl;
}

void use_pipe() {
    std::cout << "Start of use_pipe()" << std::endl;
    // Your code using pipe goes here
    // Example:
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        // handle error
    }
    std::cout << "End of use_pipe()" << std::endl;
}

void use_strerror() {
    std::cout << "Start of use_strerror()" << std::endl;
    // Your code using strerror goes here
    // Example:
    int errnum = errno; // error number
    const char* errmsg = strerror(errnum);
    // use errmsg
    std::cout << "End of use_strerror()" << std::endl;
}

void use_gai_strerror() {
    std::cout << "Start of use_gai_strerror()" << std::endl;
    // Your code using gai_strerror goes here
    // Example:
    int errcode = EAI_NONAME; // error code
    const char* errmsg = gai_strerror(errcode);
    // use errmsg
    std::cout << "End of use_gai_strerror()" << std::endl;
}

void use_errno() {
    std::cout << "Start of use_errno()" << std::endl;
    // Your code using errno goes here
    // Example:
    if (errno == EACCES) {
        // handle access denied error
    }
    std::cout << "End of use_errno()" << std::endl;
}

void use_fork() {
    std::cout << "Start of use_fork()" << std::endl;
    // Your code using fork goes here
    // Example:
    pid_t child_pid = fork();
    if (child_pid == -1) {
        // handle error
    } else if (child_pid == 0) {
        // code for child process
    } else {
        // code for parent process
    }
    std::cout << "End of use_fork()" << std::endl;
}

void use_socketpair() {
    std::cout << "Start of use_socketpair()" << std::endl;
    // Your code using socketpair goes here
    // Example:
    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        // handle error
    }
    std::cout << "End of use_socketpair()" << std::endl;
}

void use_htons_htonl_ntohs_ntohl() {
    std::cout << "Start of use_htons_htonl_ntohs_ntohl()" << std::endl;
    // Your code using htons, htonl, ntohs, ntohl goes here
    // Example:
    uint16_t port = htons(8080); // convert port number to network byte order
    uint32_t ip = htonl(0xC0A80001); // convert IP address to network byte order
    uint16_t port2 = ntohs(port); // convert port number to host byte order
    uint32_t ip2 = ntohl(ip); // convert IP address to host byte order
    std::cout << "End of use_htons_htonl_ntohs_ntohl()" << std::endl;
}

void use_select() {
    std::cout << "Start of use_select()" << std::endl;
    // Your code using select goes here
    // Example:
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    if (ready == -1) {
        // handle error
    } else if (ready == 0) {
        // timeout occurred
    } else {
        // input is available on stdin
    }
    std::cout << "End of use_select()" << std::endl;
}

void use_poll() {
    std::cout << "Start of use_poll()" << std::endl;
    // Your code using poll goes here
    // Example:
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    int timeout = 5000; // timeout in milliseconds
    int ready = poll(fds, 1, timeout);
    if (ready == -1) {
        // handle error
    } else if (ready == 0) {
        // timeout occurred
    } else {
        // input is available on stdin
    }
    std::cout << "End of use_poll()" << std::endl;
}

void use_epoll_epoll_create_epoll_ctl_epoll_wait() {
    std::cout << "Start of use_epoll_epoll_create_epoll_ctl_epoll_wait()" << std::endl;
    // Your code using epoll, epoll_create, epoll_ctl, epoll_wait goes here
    // Example:
    int epoll_fd = epoll_create(1);
    if (epoll_fd == -1) {
        // handle error
    }
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        // handle error
    }
    struct epoll_event events[10];
    int num_events = epoll_wait(epoll_fd, events, 10, -1);
    if (num_events == -1) {
        // handle error
    }
    for (int i = 0; i < num_events; i++) {
        if (events[i].data.fd == STDIN_FILENO) {
            // input is available on stdin
        }
    }
    std::cout << "End of use_epoll_epoll_create_epoll_ctl_epoll_wait()" << std::endl;
}

void use_socket_accept_listen_bind_connect_getaddrinfo_freeaddrinfo_setsockopt_getsockname_getprotobyname() {
    std::cout << "Start of use_socket_accept_listen_bind_connect_getaddrinfo_freeaddrinfo_setsockopt_getsockname_getprotobyname()" << std::endl;
    // Your code using socket, accept, listen, bind, connect, getaddrinfo, freeaddrinfo, setsockopt, getsockname, getprotobyname goes here
    // Example:
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        // handle error
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        // handle error
    }
    if (listen(sockfd, 10) == -1) {
        // handle error
    }
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addrlen);
    if (client_sockfd == -1) {
        // handle error
    }
    struct addrinfo hints;
    struct addrinfo* result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo("www.example.com", "http", &hints, &result) != 0) {
        // handle error
    }
    freeaddrinfo(result);
    int option_value = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1) {
        // handle error
    }
    struct sockaddr_in local_addr;
    socklen_t local_addrlen = sizeof(local_addr);
    if (getsockname(sockfd, (struct sockaddr*)&local_addr, &local_addrlen) == -1) {
        // handle error
    }
    struct protoent* proto = getprotobyname("tcp");
    if (proto == NULL) {
        // handle error
    }
    std::cout << "End of use_socket_accept_listen_bind_connect_getaddrinfo_freeaddrinfo_setsockopt_getsockname_getprotobyname()" << std::endl;
}

void use_fcntl_close() {
    std::cout << "Start of use_fcntl_close()" << std::endl;
    // Your code using fcntl, close goes here
    // Example:
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        // handle error
    }
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        // handle error
    }
    if (close(fd) == -1) {
        // handle error
    }
    std::cout << "End of use_fcntl_close()" << std::endl;
}

void use_read_write() {
    std::cout << "Start of use_read_write()" << std::endl;
    // Your code using read, write goes here
    // Example:
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        // handle error
    }
    char buffer[1024];
    ssize_t num_bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (num_bytes == -1) {
        // handle error
    }
    ssize_t num_written = write(fd, buffer, num_bytes);
    if (num_written == -1) {
        // handle error
    }
    std::cout << "End of use_read_write()" << std::endl;
}

void use_waitpid() {
    std::cout << "Start of use_waitpid()" << std::endl;
    // Your code using waitpid goes here
    // Example:
    pid_t child_pid = fork();
    if (child_pid == -1) {
        // handle error
    } else if (child_pid == 0) {
        // code for child process
        exit(0);
    } else {
        int status;
        pid_t terminated_pid = waitpid(child_pid, &status, 0);
        if (terminated_pid == -1) {
            // handle error
        } else if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            // handle child process exit status
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            // handle child process termination due to signal
        }
    }
    std::cout << "End of use_waitpid()" << std::endl;
}

void use_kill_signal() {
    std::cout << "Start of use_kill_signal()" << std::endl;
    // Your code using kill, signal goes here
    // Example:
    pid_t pid = getpid(); // process ID of the current process
    if (kill(pid, SIGTERM) == -1) {
        // handle error
    }
    signal(SIGINT, SIG_IGN); // ignore SIGINT signal
    std::cout << "End of use_kill_signal()" << std::endl;
}

void use_access_stat() {
    std::cout << "Start of use_access_stat()" << std::endl;
    // Your code using access, stat goes here
    // Example:
    const char* path = "file.txt";
    if (access(path, F_OK) == 0) {
        // file exists
    }
    struct stat st;
    if (stat(path, &st) == 0) {
        // use st to get file information
    }
    std::cout << "End of use_access_stat()" << std::endl;
}

void use_open() {
    std::cout << "Start of use_open()" << std::endl;
    // Your code using open goes here
    // Example:
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        // handle error
    }
    std::cout << "End of use_open()" << std::endl;
}

void use_opendir_readdir_closedir() {
    std::cout << "Start of use_opendir_readdir_closedir()" << std::endl;
    // Your code using opendir, readdir, closedir goes here
    // Example:
    DIR* dir = opendir(".");
    if (dir == NULL) {
        // handle error
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // use entry to get directory entry information
    }
    closedir(dir);
    std::cout << "End of use_opendir_readdir_closedir()" << std::endl;
}
