#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	FILE *fp;

	fp = fopen("doc1.txt","r");

	if(fp == NULL ) {

		perror("doc1.txt:");
		printf("Error occured while opening. Error number is %d \n",errno);
		exit(0);

	}else{

		printf("successfully read the file \n");
		FILE *fp2;
		fp2 = fopen("doc2.txt","w");

		if(fp2 == NULL ) {

			perror("doc2.txt:");
			printf("Error occured while opening. Error number is %d \n",errno);
			exit(0);

		}else{

			char buf[15];
			while(fscanf(fp,"%s",buf)==1){
				fprintf(fp2, "%s ",buf);	
			}

		}

		fclose(fp2);

		
	}

	fclose(fp);


return(0);
}