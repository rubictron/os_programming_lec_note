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

void * thread_f1(void * arguments);
void * thread_f2(void * arguments);
int glb_v =0;
pthread_mutex_t  mtid = PTHREAD_MUTEX_INITIALIZER;

int main(){

    int count = 1000000;
    pthread_t tid1,tid2;

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
        pthread_mutex_lock(&mtid);
        glb_v++; 
        pthread_mutex_unlock(&mtid);   
    }

    pthread_exit(NULL); 

    
}


void * thread_f2(void * arguments){

    int count =*(int *)arguments;

    for(int i=0;i<count ;i ++){
        pthread_mutex_lock(&mtid);
        glb_v--; 
        pthread_mutex_unlock(&mtid);          
    }

    pthread_exit(NULL);   
}



