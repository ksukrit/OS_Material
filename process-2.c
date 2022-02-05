#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>



/* 
0 --> stdin
1 --> stdout
2 --> stderr
*/

int main(void){
	int pfds[2]; // pipe file descriptors
	char buf[30];

	if(pipe(pfds) == -1 ){ // error
		perror("Error in making pipe \n");
		exit(1);
	}

	// printf("Writing to file descriptor %d \n",pfds[1]); // write end of the pipe
	// write(pfds[1],"test",5);
	// //write(1,"test\n",5); write to standard output
	// printf("Reading from file descriptor %d \n",pfds[0]); // read end of the pipe
	// read(pfds[0],buf,sizeof("test"));
	// printf("Read %s \n",buf);

	if(! fork()){
		// Child 
		close(pfds[1]);

		/* read from the pipe */
		read(pfds[0], buf, 5);
		printf("child read %s\n",buf);

		/* close the write end of the pipe */
		close(pfds[0]);
	}else{
		// Parent 

		close(pfds[0]);

		/* write to the pipe */
		write(pfds[1], "test", 5); 

		/* close the write end of the pipe */
		close(pfds[1]);
	}
	return 0;
}
