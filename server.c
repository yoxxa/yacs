#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int create_socket() {

	struct addrinfo hints, *serv_info;
	int sockfd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	if (getaddrinfo(NULL, "9024", &hints, &serv_info) != 0){ 	
		printf("Error with getaddrinfo()");
		return;
	}

	sockfd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);

	if (sockfd == -1) {
		printf("Error with socket()");
		return;
	}
	
	if(bind(sockfd, serv_info->ai_addr, serv_info->ai_addrlen) != 0) {
		printf("Error with bind()");
		return;
	}

	// 10 signifies num of pending connections
	listen(sockfd, 10);

	struct sockaddr_storage incoming;
	socklen_t addr_size = sizeof(incoming);	
	int new_sockfd;

	new_sockfd = accept(sockfd, (struct sockaddr *)&incoming, &addr_size);
	
	char msg[] = "Hello client!";
	
	send(new_sockfd, msg, strlen(msg) + 1, 0);

	freeaddrinfo(serv_info);
}


int main () {

	create_socket();	
        
}
