#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <strings.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include<semaphore.h>

void * thread_f1();
void * thread_f2();
void * thread_f3();

sem_t * sem1;
sem_t * sem2;
const char * name1 ="/sem_name1";
const char * name2 ="/sem_name2";



int main(){

    int count = 1000000;
    pthread_t tid1,tid2,tid3;

    sem1 = sem_open(name1,O_CREAT,0666,0);
    sem2 = sem_open(name2,O_CREAT,0666,0);

    pthread_create(&tid1,NULL,thread_f1,NULL);
    pthread_create(&tid2,NULL,thread_f2,NULL);
    pthread_create(&tid3,NULL,thread_f3,NULL);



    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    printf("\n");

    return (0);

}


void * thread_f1(){

    
    printf("Hello ");
    sem_post(sem1);
    pthread_exit(NULL);
    


    
}
void * thread_f2(){

    sem_wait(sem1);
    printf("I am ");
    sem_post(sem2);
    pthread_exit(NULL); 

    
}
void * thread_f3(){

    sem_wait(sem2);
    printf("Sandakalum");
    pthread_exit(NULL); 

    
}





