#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int shmid;
  char *shmPtr;
  int n;
  if(fork()==0){
    //child process
    sleep(5);
    if((shmid = shmget(2041,32,0))==-1){
      exit(1);
    }
    shmPtr = shmat(shmid,0,0);
    if(shmPtr == (char*)-1){
      exit(2);
    }
    printf("Child is reading ...\n");
    for(n = 0;n<26;n++){
      putchar(shmPtr[n]);
    }
    putchar('\n');
  }
  else{
    //parent
    if((shmid = shmget(2041,32,0666 | IPC_CREAT)) == -1){
      exit(3);
    }
    shmPtr = shmat(shmid,0,0);
    if(shmPtr == (char*)-1){
      exit(4);
    }
    for(n = 0;n<26;n++){
      shmPtr[n] = 'a'+n;
    }
    printf("Parent is writing....\n");
    for(n = 0;n<26;n++){
      putchar(shmPtr[n]);
    }
    putchar('\n');
    wait(NULL);
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
      exit(5);
    }

  }
  return 0;
}