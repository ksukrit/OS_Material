#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFF_SIZE 5
#define NP 3
#define NC 3
#define NITERS 4

typedef struct{
  int buf[BUFF_SIZE];
  int in, out;
  sem_t full, empty;
  pthread_mutex_t mutex;
}sbuf_t;

sbuf_t shared;

void* Producer(void* argc){
  int i,item;
  long index = (long)argc;
  for(i=0;i<NITERS;i++){
    item = i;//produce an item.
    sem_wait(&shared.empty);//wait for an empty slot.
    pthread_mutex_lock(&shared.mutex);//lock the buffer.
    shared.buf[shared.in] = item;
    shared.in = (shared.in+1)%BUFF_SIZE;
    printf("Producer %ld has produced item %d\n",index,item );
    pthread_mutex_unlock(&shared.mutex);//release the buffer
    sem_post(&shared.full);//signall that there is one item ready to be consumed .
    if(i%2 == 1){
      sleep(1);
    }
  }
  return 0;
}

void* Consumer(void* arg){
  int i,item;
  long index = (long)arg;
  for(i=0;i<NITERS;i++){
    sem_wait(&shared.full);//check if there is atleast one item.
    pthread_mutex_lock(&shared.mutex);//lock the buffer
    item = shared.buf[shared.out];
    shared.out = (shared.out+1)%BUFF_SIZE;
    printf("Consumer %ld has consumed item %d\n", index,item);
    pthread_mutex_unlock(&shared.mutex);//unlock the buffer
    sem_post(&shared.empty);//signal that there is one more slot avaliable.
    if(i%2 == 1){
      sleep(1);
    }
  }
  return 0;
}

int main(){
  pthread_t idP , idC;
  long index;
  sem_init(&shared.full,0,0);// FIRST 0:THREADS OF A SINGLE PROCESS THE SEMAPHORE IS SHARED IN
  sem_init(&shared.empty,0,BUFF_SIZE);
  for(index = 0;index <NP; index++){
    pthread_create(&idP, NULL, Producer, (void*)index);
  }
  for(index = 0;index <NC; index++){
    pthread_create(&idC, NULL, Consumer, (void*)index);
  }
  pthread_exit(NULL);
  return 0;
}
