#include "header.hpp"

int main(int argc, char **argv) {
	std::cout << "the main" << std::endl;
	// use_execve();
	use_dup();
	use_dup2();
	use_pipe();
	use_strerror();
	use_gai_strerror();
	use_errno();
	use_fork();
	use_socketpair();
	use_htons_htonl_ntohs_ntohl();
	use_select();
	use_poll();
	use_epoll_epoll_create_epoll_ctl_epoll_wait();
	use_socket_accept_listen_bind_connect_getaddrinfo_freeaddrinfo_setsockopt_getsockname_getprotobyname();
	use_fcntl_close();
	use_read_write();
	use_waitpid();
	use_kill_signal();
	use_access_stat();
	use_open();
	use_opendir_readdir_closedir();

	return 0;
}
/*
c++ main.cpp extra.cpp -o cool-lstdc++ -std=c++17
./cool
c++ main.cpp extra.cpp -o cool -lstdc++ && ./cool
*/
