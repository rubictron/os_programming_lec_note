#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>



struct msg
{
	long type;
	char text[20];

};


struct msg createMsg(long type,char text[]);


int main()
{
	
	key_t key_for_MQ = ftok("file1.txt",22);//creating a key

	int MQID = msgget(key_for_MQ,IPC_CREAT|0666);//creating a MQ //IPC_PRIVATE

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
				struct msg msgsC2[4];

				for(int i=0;i<4;i++){
					msgrcv(MQID,&msgsC2[i],sizeof(msgsC2[i].text),0,IPC_NOWAIT); 
				}

				printf("I am Child C2 with PID %d. I recived \n %s %s %s %s \n",getpid(),
										msgsC2[0].text,
										msgsC2[1].text,
										msgsC2[2].text,
										msgsC2[3].text);
				waitpid(PID2,NULL,0);
				printf("Child C2 terminated\n");
				exit(0);

				break;
				
			default	: // child C1
			
				getpid();
				struct msg msgsC1[3];

				for(int i=0;i<3;i++){
					msgrcv(MQID,&msgsC1[i],sizeof(msgsC1[i].text),0,IPC_NOWAIT); 
				}

				printf("I am Child C1 with PID %d. I recived \n %s %s %s \n",getpid(),
										msgsC1[0].text,
										msgsC1[1].text,
										msgsC1[2].text);
				printf("Child C1 terminated\n");
				exit(0);
			
			break;
		}
		default	: // Parent P1
				getpid();
				struct msg msgs[8];
				msgs[0] = createMsg(100,"\nfirst message\n");
				msgs[1] = createMsg(200,"\nsecond message\n");
				msgs[2] = createMsg(300,"\nthird message\n");
				msgs[3] = createMsg(100,"\nfourth message\n");
				msgs[4] = createMsg(200,"\nfifth message\n");
				msgs[5] = createMsg(100,"\nsixth message\n");
				msgs[6] = createMsg(300,"\nseventh message\n");
				msgs[7] = createMsg(150,"\neighth message\n");


				for(int i=0;i<8;i++){
					msgsnd(MQID,&msgs[i],sizeof(msgs[i].text),0); //flag 0 if msg full wait
				}

				waitpid(PID1,NULL,0);

				struct msg msgFinal;
				msgrcv(MQID,&msgFinal,sizeof(msgFinal.text),300,IPC_NOWAIT);
				printf("I am Parent with PID %d. I recived \n %s \n",getpid(),msgFinal.text);
				msgctl(MQID, IPC_RMID, NULL);
				exit(0);

			
			break;
			
	
	}


	return 0;
}


struct msg createMsg(long type,char text[]){

struct msg newMsg;
newMsg.type = type;
strcpy(newMsg.text,text);

return newMsg;

}