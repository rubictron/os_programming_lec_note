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

void * thread_f1(void * arguments);
void * thread_f2(void * arguments);
int glb_v =0;


sem_t * sem1;
const char * name1 ="/sem_name1";



int main(){

    int count = 1000000;
    pthread_t tid1,tid2;

    sem1 = sem_open(name1,O_CREAT,0666,1);

    pthread_create(&tid1,NULL,thread_f1,(void *)&count);
    pthread_create(&tid2,NULL,thread_f2,(void *)&count);


    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    printf("glb_v = %d \n",glb_v);

    return (0);

}


void * thread_f1(void * arguments){

    int count =*(int *)arguments;

    for(int i=0;i<count ;i ++){
        sem_wait(sem1);
        glb_v++; 
        sem_post(sem1);
    }

    pthread_exit(NULL); 

    
}


void * thread_f2(void * arguments){

    int count =*(int *)arguments;

    for(int i=0;i<count ;i ++){
        sem_wait(sem1);
        glb_v--; 
        sem_post(sem1);         
    }

    pthread_exit(NULL);   
}



