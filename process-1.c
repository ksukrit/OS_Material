#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void){
	int a =10, status;
	pid_t p;
	p = fork();
	if(p == 0){
		printf("Child process  \n");
		printf("Child: Child pid is %d\n", getpid()); 
		printf("Child: Parent pid is %d\n", getppid()); 
		printf("This is the child before exec()\n"); 
		printf("Current pid is %d\n",getpid()); 
		execlp("ls", "os", "-al", NULL); 
		//execlp("gcc", nos", "program.c","-o program.out", NULL); 
		printf("This is after using exec()\n"); 
	}else if( p > 0) {
		//sleep(5);
		wait(&status);
		printf("Parent process \n");
		printf("Parent: Child's pid is %d\n",p); 
		/* 
		In the parent process the fork() command returns 
		the child pid (pid_t)
		getpid() return the pid of the current process
		getppid() return the pid of the parent of the process 
		parent of the child process - main process
		parent of our main process - bash/terminal
		*/
		printf("Parent: Parent's pid is %d\n", getpid()); 
		printf("Parent: Grandparent's pid is %d\n",getppid()); 
	}else {
		printf("Error in fork() \n");
	}

	return 0;
}
