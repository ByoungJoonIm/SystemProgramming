#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "message.h"

int main(int argc, char *argv[]){
	void *shared_memory = (void *)0;
	int shmid;
	int fd;
	int pid;

	/*
	 	create shared memory
	 */
	shmid = shmget((key_t)COMMON_KEY, MSG_SIZE, 0666 | IPC_CREAT);
	if(shmid == -1)
		return -1;

	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *) - 1)
		return -1;
	
	/*
	 	load sh to shared memory
	 */
	fd = open("cmd.sh", O_RDONLY);
	memset(shared_memory, 0, MSG_SIZE);
	read(fd, shared_memory, MSG_SIZE);
	close(fd);

	signal(SIGCHLD, SIG_IGN);//parent doesn't wait child
	/*
	 	fork
	 */
	pid = fork();

	if( pid == 0){	//if child
		printf("%s\n", (char*)shared_memory);
		if( shmdt(shared_memory) == -1)
			return -1;
		exit(EXIT_SUCCESS);
	} 


	
	//   detach and destroy shared memory
	if( shmdt(shared_memory) == -1)
		return -1;
	if( shmctl(shmid, IPC_RMID, 0) == -1)
		return -1;
	
}
