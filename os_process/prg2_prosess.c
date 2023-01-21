#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(){

int pipe_fd[2];
if(pipe(pipe_fd) == -1 ){
	perror("pipe");
}
else{

pid_t PID;

switch(PID = fork()){
	case -1:
		perror("fork");
		exit(PID);
		break;

	case 0:
		close(pipe_fd[1]);
		sleep(1);
		char *buf[50];
		read(pipe_fd[0],buf,sizeof(buf));
		printf("this is chiled procss msg is %s \n", buf );
		printf("%s %d \n","pid = " ,getpid());
		exit(0);
		break;
	default:
		close(pipe_fd[0]);
			char msg[] = "Message from parent ";
			write(pipe_fd[1],msg,sizeof(msg));
			printf("%s %d \n","message written by parent " ,getpid());
			exit(0);
		break;

	}

}

	return 0;
}		 