#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5
int sum = 0;
int inc = 5;
pthread_mutex_t lock;

void *func(void *val){
  pthread_mutex_lock(&lock);
  //critical section begins
  sum+=inc;
  printf("Value: %d\n",sum);
  inc += 5;
  pthread_mutex_unlock(&lock);
  //critical section ends
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[N];
  int i;
  pthread_mutex_init(&lock, NULL);
  for(i=0;i<N;i++){
    if(pthread_create(&t[i], NULL, func, NULL)){
      printf("Error in creating thread %d\n",i);
      return EXIT_FAILURE;
    }
  }
  for(i=0;i<N;i++){
    pthread_join(t[i],NULL);
  }
  return 0;
}
