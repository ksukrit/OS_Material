#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
int sum = 0;

// gcc -pthread threads-2.c -o threads-2.out

typedef struct {
	long int begin;
	long int end;
} my_struct;

void *func(void *val){
	//my_struct * s = (my_struct *)val;
	my_struct * s =  val;
	int j;

	printf("start : %ld end : %ld \n",s->begin,s->end);
	for( j = s->begin; j <= s->end; j++){
		sum += j;
	}
	return NULL;
}

int main(int argc, char *argv[]){
	int t_c = atoi(argv[1]);
	printf("Num of threads %d \n",t_c);
	pthread_t threads[t_c];
	long int last = atoi(argv[2]);
	printf("Last %ld \n", last);
	int i;
	
	for(i = 0; i <(t_c); i++){
		my_struct * s = malloc(sizeof(my_struct));

		s->begin = (last/t_c)*i +1;
		s->end = ((last/t_c)*(i+1));
		
		if(pthread_create(&threads[i],NULL,func, s)){
			// Error happened.
			printf("Error making thread %d \n", i);
			exit(1);
		}
		//pthread_join(threads[i],NULL);
	}


	for(i = 0; i < t_c; i++){
		pthread_join(threads[i],NULL);
	}

	printf("Sum is %d \n", sum);
	return 0;
}
