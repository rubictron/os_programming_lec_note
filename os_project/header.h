#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>


int MQID;


struct msg
{
	long type;
	char text[50];

};


struct msg createMsg(long type,char text[]){

struct msg newMsg;
newMsg.type = type;
strcpy(newMsg.text,text);

return newMsg;

}

int sendMsg(char * process,struct msg msg){

	//strcpy(msg.text,strcat(msg.text, process));
	msgsnd(MQID,&msg,sizeof(msg.text),0);
	printf("I am %s with PID %d. I send \t\t %s \n",process,getpid(),msg.text);
	return 0;	
}


struct msg reciveMsg(char * process){
	struct msg msgpRecived;
	msgrcv(MQID,&msgpRecived,sizeof(msgpRecived.text),0, MSG_NOERROR);
	printf("I am %s with PID %d. I recived \t %s \n",process,getpid(),msgpRecived.text);
	return msgpRecived;
}


void chiledMethod(char p[],int PID){
	getpid();
	char pmt[] = "Hello my child Iam Parent ";
	char cmt[] = "Hello my mom Iam Child ";
	strcat(pmt,p);
	strcat(cmt,p);
	struct msg resiveMsg = reciveMsg(p);
	struct msg parentMsg = createMsg(100,pmt);
	struct msg chiledMsg = createMsg(100,cmt);
	sendMsg(p,parentMsg);
	waitpid(PID,NULL,0);
	resiveMsg = reciveMsg(p);
	sendMsg(p,chiledMsg);
	printf("Child %s terminated\n",p);
	exit(0);
	
}