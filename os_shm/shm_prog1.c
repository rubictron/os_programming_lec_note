#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/shm.h>



struct msg
{
	long type;
	char text[20];

};


struct msg createMsg(long type,char text[]);


int main()
{
	
	key_t key_for_SM1 = ftok("file1.txt",22);//creating a key
	key_t key_for_SM2 = ftok("file1.txt",44);//creating a key

	int SMID1 = shmget(key_for_SM1,4096,IPC_CREAT|0666);//creating a SM1
	int SMID2 = shmget(key_for_SM2,4096,IPC_CREAT|0666);//creating a SM2



	int PID1;

	switch(PID1 = fork()){
		case -1 : // error 
			perror("Chiled1");
			exit(0);
			break;
		case  0 : // child C1
			getpid();
			int PID2;
			switch(PID2 = fork()){
			case -1 : // error 
				perror("Child2");
				exit(0);
				break;
			case  0 : // child C2
				getpid();

				char * shmptrc2;
				char bufc2[50];
				char msg[] ="Responce from child C2";
				shmptrc2 = (char *)shmat(SMID2,NULL,SHM_W|SHM_R);
				strcpy(bufc2,shmptrc2);
				printf("C2 recived: %s\n",shmptrc2);
				strcpy(shmptrc2,msg);
				printf("C2 sent: %s\n",shmptrc2);

				exit(0);

				break;
				
			default	: // child C1
			
				getpid();
				char * shmptrc1_a;
				char * shmptrc1_b;
				char bufc1a[50];
				char bufc1b[50];
				shmptrc1_a = (char *)shmat(SMID1,NULL,SHM_W|SHM_R);
				shmptrc1_b = (char *)shmat(SMID2,NULL,SHM_W|SHM_R);


				strcpy(bufc1a,shmptrc1_a);
				printf("C1 recived: %s\n",shmptrc1_a);
				char msgc1a[] = "Response from child C1";
				char msgc1b[] = "Response from parent C1";

				strcpy(shmptrc1_a,msgc1a);
				strcpy(shmptrc1_b,msgc1b);
				printf("C1 sent: %s\n",shmptrc1_b);

				waitpid(PID2,NULL,0);

				strcpy(bufc1b,shmptrc1_b);
				printf("C1 recived: %s\n",shmptrc1_b);	


				exit(0);
			
			break;
		}
		default	: // Parent P1
				getpid();
				
				char msgp1[] = "message from parent p1";
				char * shmptrp1;
				shmptrp1 = (char *)shmat(SMID1,NULL,SHM_W|SHM_R);
				strcpy(shmptrp1,msgp1);//write into memory
				printf("P1 sent: %s\n",shmptrp1);
				sleep(1);
				waitpid(PID1,NULL,0);

				char bufp1[50];
				strcpy(bufp1,shmptrp1);
				printf("P1 read: %s\n",shmptrp1);

				exit(0);
	
			break;
			
	
	}

	shmctl(SMID1,IPC_RMID, NULL);
	shmctl(SMID2,IPC_RMID, NULL);

	return 0;
}


struct msg createMsg(long type,char text[]){

struct msg newMsg;
newMsg.type = type;
strcpy(newMsg.text,text);

return newMsg;

}