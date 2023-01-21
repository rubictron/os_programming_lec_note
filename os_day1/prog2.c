#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

int *heap_vama malloc ();
*heap_value = 500;
	FILE *fp;

	fp = fopen("doc1.txt","w");

	if(fp == NULL ) {

		perror("doc1.txt:");
		printf("Error occured while opening. Error number is %d \n",errno);
		exit(0);

	}else{

		int size;
		printf("Enter the size of name : \n");
		scanf("%d",&size);

		char name[size];
		printf("Enter the name : \n");
		scanf("%s",name);

		char age[2];
		printf("Enter the age : \n");
		scanf("%s",age);

		fprintf(fp,"Name is %s and age is %s \n",name,age);	

		

		fclose(fp);




		
	}


return(0);
}