#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF 1024 //sizeof buf

int main(void){
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char buf[BUF];

	// create a socket for the client
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// name the socket as agreed with the server
	// set the address to the server's address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);

	// connect to the server's socket
	result = connect(sockfd, (struct sockaddr *) &address, len);

	if( result == -1 ) {
		perror("oops: client1");
		exit(1);
	}

	sprintf(buf, "%s", "test");

	// read and write via sockfd
	write(sockfd, buf, sizeof(buf));
	read(sockfd, buf, sizeof(buf));
	printf("[client] msg from server = %s\n", buf);
	close(sockfd);

	return 0;
}
