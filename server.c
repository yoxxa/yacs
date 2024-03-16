#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

void set_struct(struct addrinfo *hints) {
	memset(hints, 0, sizeof(hints));
	hints->ai_flags = AI_PASSIVE;
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_protocol = 0;
}

int create_socket_and_bind(int *sockfd, struct addrinfo *serv_info) {
	*sockfd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);

	if (*sockfd == -1) {
		printf("Error with socket()");
		return;
	}
	
	if(bind(*sockfd, serv_info->ai_addr, serv_info->ai_addrlen) != 0) {
		printf("Error with bind()");
		return;
	}
	return *sockfd;
}

void handle_connection(int *sockfd) {

	// 10 signifies num of pending connections
	listen(*sockfd, 10);

	struct sockaddr_storage incoming;
	socklen_t addr_size = sizeof(incoming);	
	int new_sockfd;

	new_sockfd = accept(*sockfd, (struct sockaddr *)&incoming, &addr_size);

	//printf("[+] Connection Initiated");

	char msg[] = "Hello client!";
	
	if(send(new_sockfd, msg, strlen(msg) + 1, 0) == -1) {
		printf("Error with send()");
		return;
	}	
	//printf("[+] Message Sent");	
}

int start_server() {

	struct addrinfo hints, *serv_info;
	int sockfd;

	set_struct(&hints);

	if (getaddrinfo(NULL, "9024", &hints, &serv_info) != 0){ 	
		printf("Error with getaddrinfo()");
		return;
	}

	sockfd = create_socket_and_bind(&sockfd, serv_info);

	while (1) {
		
		handle_connection(&sockfd);

	}

	freeaddrinfo(serv_info);
}


int main () {

	start_server();	
        
}
