#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

sem_t sem;
int counter;

void* handler(void* ptr){
  int x = (int) ptr;
  printf("Thread %d: waiting to enter the critical section...\n",x);
  sem_wait(&sem);
  //critical section
  printf("Thread %d in now in the critical section...\n", x);
  printf("Thread: %d | counter value: %d\n",x,counter);
  printf("Thread %d incrementing the value of counter ...\n", x);
  counter++;
  printf("Thread %d | New value of counter: %d\n",x,counter);
  printf("Thread %d is exiting the critical section\n", x);
  //critical section end
  sem_post(&sem);//signal()
  pthread_exit(0);
}

int main(){
  int i[2] = {0,1};
  pthread_t  thread_a, thread_b;

  sem_init(&sem,0,1);//1 initial value.
  pthread_create(&thread_a, NULL, (void *)&handler, (void*)i[0]);
  pthread_create(&thread_b, NULL, (void *)&handler, (void*)i[1]);

  pthread_join(thread_a,NULL);
  pthread_join(thread_b,NULL);
  sem_destroy(&sem);
  return 0;
}
