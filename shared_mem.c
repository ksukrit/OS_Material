#include<stdio.h>
#include<stdlib.h>

#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>

#include <string.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


int main(void){
  int shmid;
  char *shmPtr;
  int n;

  if(fork() == 0){
    // child proc
    sleep(5);
    if( (shmid = shmget(2041,32,0) ) == -1){
      perror("Error in shmget\n");
      exit(1);
    }
    shmPtr = shmat(shmid,0,0);
    if(shmPtr == (char*)-1){
      perror("Error attaching \n");
      exit(1);
    }

    printf("Child is reading \n");
    for(n = 0; n < 26; n++){
      putchar(shmPtr[n]);
    }
    putchar('\n');
  }else {
    if( (shmid = shmget(2041,32,0666 | IPC_CREAT))== -1){
      perror("Error in shmget\n");
      exit(1);
    }
    shmPtr = shmat(shmid,0,0);

    if(shmPtr == (char*)-1){
      perror("Error attaching \n");
      exit(1);
    }

    for(n = 0; n < 26; n++){
      shmPtr[n] = 'a' + n; 
    }
    printf("Parent is writing \n");
    for(n = 0; n < 26; n++){
      putchar(shmPtr[n]);
    }
    putchar('\n');
    wait(NULL);
    if(shmctl(shmid,IPC_RMID,NULL) == -1){
      exit(1);
    }
  }

  return 0;
}