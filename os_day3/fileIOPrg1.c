#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	int fd;
	fd = open("doc1.txt",O_RDWR|O_CREAT,0666);//S_IRUSR|S_IWUSR

	if(fd == -1) {
		perror("doc1.txt:");
		printf("Error occured while opening. Error number is %d \n",errno);
		exit(0);

	}else{

		// int ss;
		// printf("Enter the size of name : \n");
		// scanf("%d",&ss);

		// int s =ss;

		// char name[ss];
		// printf("Enter the name : \n");
		// scanf("%s",name);

		// char age[2];
		// printf("Enter the age : \n");
		// scanf("%s",age);

		// char char1[15] = "your name is ";
		// write(fd,char1,13);
		// write(fd,name,s);

		// char char2[15] = "\nyour age is ";
		// write(fd,char2,13);
		// write(fd,age,2);

		char buffer[30];
		int returnVal;
		returnVal = read(fd,buffer,30);

		if(returnVal == -1){
			perror("doc1.txt:");
			printf("Error occured while reading. Error number is %d \n",errno);
			exit(1);
		}
		else{
		
			printf("%s\n",buffer);
		}

		close(fd);




		
	}


return(0);
}