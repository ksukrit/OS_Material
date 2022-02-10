#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
<<<<<<< HEAD


int main(void){
	int shmid;
	char *shmPtr;
	int n;

	if(fork() == 0){
		// child proc
		//sleep(5);
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
		//wait(NULL);
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
=======
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
>>>>>>> ba868e5702029905bbae459d83c081f7aab02409
