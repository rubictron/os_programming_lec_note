#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(){

int pipe1_fd[2];
int pipe2_fd[2];
if(pipe(pipe1_fd) == -1 ){
	perror("pipe1");
}
else if(pipe(pipe2_fd) == -1 ){
	perror("pipe2");
}
else{

pid_t PID;

switch(PID = fork()){

	case -1:
		perror("fork");
		exit(PID);
		break;

	case 0:
		if(close(pipe1_fd[1])== -1 ){perror("close p1 fd0");exit(0);} // p to c
		if(close(pipe2_fd[0])== -1 ){perror("close p2 fd1");exit(0);} // c to p

		sleep(1);
		char *bufc[50];
		read(pipe1_fd[0],bufc,sizeof(bufc));
		printf("this is chiled procss(%d) msg is %s \n",getpid(), bufc );

		char msgc[] = "Message from chiled";
		write(pipe2_fd[1],msgc,sizeof(msgc));

		exit(0);
		break;

	default:
		if( close(pipe1_fd[0])== -1 ){perror("close p1 fd1");exit(0);} // p to c
		if( close(pipe2_fd[1])== -1 ){perror("close p2 fd0");exit(0);} // c to p

		char msgp[] = "Message from parent ";
		write(pipe1_fd[1],msgp,sizeof(msgp));

		waitpid(PID,NULL,0);

		char *bufp[50];
		read(pipe2_fd[0],bufp,sizeof(bufp));
		printf("this is parent procss(%d) msg is %s \n",getpid(), bufp );

		

		exit(0);
		break;

	}

}

	return 0;
}		 