#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int data_v = 100;

int main(){

int stack_v =1000;

int *heap_v  = 10000;

pid_t PID;

switch(PID = fork()){
	case -1:
		perror("fork");
		exit(PID);
		break;

	case 0:
		stack_v = 2000;
		data_v = 20;
		*heap_v = 20000;
		break;
	default:
		sleep(2);
		break;

}


printf("this %s prossecces with %d datav is %d ,stack_v %d heap_v is %d \n",
 ((PID==0)?"chiled":"parent"),getpid(),data_v,stack_v, heap_v );

	return 0;
}		 