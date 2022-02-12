#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
int sum = 0;

// gcc -pthread threads-2.c -o threads-2.out

void *func(void *i){
	int *j =  i; // without explicit cast
	//int *j = (int *) i; // with cast
	sum += *j;
	printf(" Executing thread %d \n", *j);
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int data[NUM_THREADS];
	int i;

	if(argc != NUM_THREADS + 1){
		printf("No of arguements should equal no of threads \n");
		exit(1);

	}

	for(i = 0; i < NUM_THREADS; i++){
		data[i] = atoi(argv[i+1]);
		if(pthread_create(&threads[i],NULL,func, (void *)&data[i])){
			// Error happened.
			printf("Error making thread %d \n", i);
			exit(1);
		}
	}

	/*
	Ensure that all threads have computed the values 
	threads join in order
	if this is removed irrespective of whether threads 
	are finished or not the value of sum is printed.
	*/
	for(i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i],NULL);
	}

	printf("Sum is %d \n", sum);
	return 0;
}