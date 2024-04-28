#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

// Function declarations
void use_execve();
void use_dup();
void use_dup2();
void use_pipe();
void use_strerror();
void use_gai_strerror();
void use_errno();
void use_fork();
void use_socketpair();
void use_htons_htonl_ntohs_ntohl();
void use_select();
void use_poll();
void use_epoll_epoll_create_epoll_ctl_epoll_wait();
void use_socket_accept_listen_bind_connect_getaddrinfo_freeaddrinfo_setsockopt_getsockname_getprotobyname();
void use_fcntl_close();
void use_read_write();
void use_waitpid();
void use_kill_signal();
void use_access_stat();
void use_open();
void use_opendir_readdir_closedir();

#endif /* FUNCTIONS_HPP */
