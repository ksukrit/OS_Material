#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>




int main(void){
	int pfds[2],s; // pipe file descriptors
	pid_t pid;


	if(pipe(pfds) == -1 ){ // error
		perror("Error in making pipe \n");
		exit(1);
	}


	pid = fork();
	if(pid == 0){
		dup2(pfds[1],1);
		close(pfds[0]);
		if(execlp("ls","ls",NULL) == -1){
			perror("Error in execlp");
			exit(1);
		}
	}else {
		if(fork() == 0){
			dup2(pfds[0],0);
			close(pfds[1]);
			if(execlp("wc","wc","-l",NULL) == -1){
				perror("Error in execlp 2");
				exit(1);
			}
		}else{
			close(pfds[0]);
			close(pfds[1]);
			wait(&s);
			wait(&s);
		}
	}
	return 0;
}
