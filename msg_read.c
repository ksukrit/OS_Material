#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>

struct my_msgbuf {
	long mtype;
	char mtext[200];
};


int main(void){
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if( (key = ftok("msg_queue.c",'B')) == -1){
		perror(" error in ftok() \n");
		exit(1);
	}

	if ( (msqid = msgget(key, 0644)) == -1){
		perror("Error in getting msgget() \n");
		exit(2);
	}

	printf("Reader is ready \n");
	while(1){
		if(msgrcv(msqid,&buf,sizeof buf.mtext,0,0) == -1){
			perror(" error in reading message \n ");
			exit(3);

		}

		printf("Message received is %s \n", buf.mtext);
	}
	

	return 0;
}