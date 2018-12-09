#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "server_list.h"
#include "shm_key.h"

int main(int argc, char *argv[]){
	void *shared_memory = (void *)0;
	int shmid;
	int fd;
	int pid;
	int status;
	Server server;
	int sh_size;
	struct stat st;

	if( argc != 2 ){
		printf("usage : ./client sh_file < server_list\n");
		exit(EXIT_FAILURE);
	}
	/*
	 	get sh_file size
		shared memory size will be this size + 1
	 */
	stat(argv[1], &st);
	sh_size = st.st_size;

	/*
	 	create shared memory
	 */
	shmid = shmget((key_t)COMMON_KEY, sh_size + 1, 0666 | IPC_CREAT);
	if(shmid == -1)
		return -1;

	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *) - 1)
		return -1;

	/*
	 	load sh to shared memory
	 */
	fd = open("cmd.sh", O_RDONLY);
	memset(shared_memory, 0, sh_size + 1);
	read(fd, shared_memory, sh_size + 1);
	close(fd);

	//signal(SIGCHLD, SIG_DFL);//parent doesn't wait child

	/*
	 	read server list
	 */
	while(scanf("%20s\t%20s\t%10s", server.name, server.ip, server.port) > 0){
		if( *server.name == '#' )
			continue;
		/*
		   fork
		 */
		pid = fork();

		if( pid == 0){	//if child
			struct sockaddr_in address;
			int sock_len;
			int sockfd;
			int rs_len;
			char *rs;
			
			sockfd = socket(AF_INET, SOCK_STREAM, 0);

			address.sin_family = AF_INET;
			address.sin_addr.s_addr = inet_addr(server.ip);
			address.sin_port = htons(atoi(server.port));
			sock_len = sizeof(address);

			if( connect(sockfd, (struct sockaddr*)&address, sock_len) == -1){
				printf("%s connect failure!\n", server.name);
				exit(EXIT_FAILURE);
			}

			
			write(sockfd, &sh_size, sizeof(int));		//send sh_file size first
			write(sockfd, shared_memory, sh_size);
			read(sockfd, &rs_len, sizeof(int));
			rs = (char*)malloc(rs_len);
			memset(rs, 0, rs_len);
			read(sockfd, rs, rs_len);
			printf("[%s(%s:%s) result]\n%s\n\n", server.name,server.ip, server.port, rs);
			free(rs);
			
			close(sockfd);



#ifdef DEBUG
			printf("name : %s\nip : %s\nport : %s\n", server.name, server.ip, server.port);
			printf("%s\n", (char*)shared_memory);
#endif
			if( shmdt(shared_memory) == -1)
				return -1;
			exit(EXIT_SUCCESS);
		}

	}

	while( wait(&status) > 0);
#ifdef DEBUG
	printf("parent will die!\n");
#endif
	
	//   detach and destroy shared memory
	if( shmdt(shared_memory) == -1)
		return -1;
	if( shmctl(shmid, IPC_RMID, 0) == -1)
		return -1;
}
