#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>


int main(void){
	int pfds[2],pfds_1[2],s; // pipe file descriptors
	pid_t pid;


	if(pipe(pfds) == -1  || pipe(pfds_1) == -1){ // error
		perror("Error in making pipe \n");
		exit(1);
	}


	pid = fork();
	if(pid == 0){
		printf("Child 1 \n");
		dup2(pfds[1],1);
		close(pfds[0]);
		close(pfds_1[0]);
		close(pfds_1[1]);
		if(execlp("ls","ls","-l",NULL) == -1){
			perror("Error in execlp 1");
			exit(1);
		}
	}else {
		if(fork() == 0){
			printf("Child  2 \n");
			dup2(pfds[0],0);
			dup2(pfds_1[1],1);
			close(pfds[1]);
			close(pfds_1[0]);
			if(execlp("grep","grep","Feb",NULL) == -1){
				perror("Error in execlp 2");
				exit(1);
			}
		}else{
			if(fork() == 0){
				printf("Child  3 \n");
				dup2(pfds_1[0],0);
				close(pfds[0]);
				close(pfds[1]);
				//close(pfds_1[0]);
				close(pfds_1[1]);
				if(execlp("wc","wc","-l",NULL) == -1){
					perror("Error in execlp 3");
					exit(1);
				}
			}else {
				close(pfds[0]);
				close(pfds[1]);
				close(pfds_1[0]);
				close(pfds_1[1]);
				wait(&s);
				wait(&s);
				wait(&s);	
			}
		}
	}
	return 0;
}
