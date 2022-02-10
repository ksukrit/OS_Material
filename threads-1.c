#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

// compile command 
// gcc -pthread threads-1.c -o threads-1.out

void *PrintHello(void *threadid){
	long tid;
	tid = (long) threadid;
	printf("Thread #  %ld\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for(t = 0; t < NUM_THREADS;  t++){
		printf("In main : creating thread no %ld\n",t);
		rc = pthread_create(&threads[t],NULL,PrintHello, (void *)t);
		if(rc){
			printf("Error in making thread %d\n",rc);
			exit(1);
		}
		pthread_join(threads[t],NULL); // Required to maintain async execution
	}
	pthread_exit(NULL);
	return 0;
}