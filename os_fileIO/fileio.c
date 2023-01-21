#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


int main()
{

int fd1;
fd1 = open("Doc1.txt",O_RDONLY,0666);

if(fd1 == -1 )
{
    perror("Doc1.txt");
    printf("Document can not opened.Error number is %d",errno);
    exit(0);



  
}    
else
{
    char buf1[16],buf2[11];

    lseek(fd1,15,SEEK_SET);
    read(fd1,buf1,16);

    lseek(fd1,10,SEEK_CUR);
    read(fd1,buf2,11);

    int fd2;
    fd2 = open("Doc2.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd1 == -1 )
    {
        perror("Doc2.txt");
        printf("Document can not opened.Error number is %d",errno);
        exit(0);
    }
    else
    {
        char buf3[3]  = "   ";


        write(fd2,buf1,sizeof(buf1)) ; 
        write(fd2,buf3,sizeof(buf2)) ; 
        write(fd2,buf2,sizeof(buf3)) ; 

        printf("file written successfully\n");
    }


    close(fd2);

}

close(fd1);

	
	 

    return 0;
}