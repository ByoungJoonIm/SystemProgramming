#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int server_sockfd;

static void sigint_handler(int signo){
	printf("exit...\n");
	close(server_sockfd);
	fflush(stdout);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
	int client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int fd;
	int size;
	char *buf;
	const char* sh_file = "cmd.sh";
	const char* rs_file = "result";
	char cmd[128];
	struct stat st;

	if( argc != 2){
		printf("usage: ./server port_number");
		exit(EXIT_FAILURE);
	}

	/*
	 	add sig handler
	 */
	if( signal(SIGINT, sigint_handler) == SIG_ERR){
		printf("cannot handle sigint!\n");
		exit(EXIT_FAILURE);
	}

	/*
	 	bind and listen
	 */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept from any IP
	server_address.sin_port = htons(atoi(argv[1]));
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 5);

	while(1){
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, 
				(struct sockaddr *)&client_address, &client_len);

		/*
		 	read sh_size and sh
		 */
		read(client_sockfd, &size, sizeof(int));
		buf = (char*)malloc(size);
		read(client_sockfd, buf, size);

		/*
		 	save sh as a file
		 */
		fd = open(sh_file, O_CREAT | O_TRUNC | O_WRONLY, 0700);
		write(fd, buf, size);
		close(fd);
		free(buf);

		/*
		 	execute sh
			./sh_file > rs_file
		 */
		strcpy(cmd, "./");
		strcat(cmd, sh_file);
		strcat(cmd, " > ");
		strcat(cmd, rs_file);
		system(cmd);

		/*
		 	load rs and send
		 */
		stat(rs_file, &st);
		size = st.st_size;
		buf = (char*)malloc(size);

		fd = open(rs_file, O_RDONLY);
		read(fd, buf, size);
		close(fd);
		write(client_sockfd, &size, sizeof(int));
		write(client_sockfd, buf, size);
		free(buf);

		close(client_sockfd);
	}

	return 0;
}
