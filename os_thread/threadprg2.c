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
pthread_cond_t cond1  = PTHREAD_COND_INITIALIZER;  
pthread_cond_t cond2  = PTHREAD_COND_INITIALIZER; 

int main(){
    int count = 0;
    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,thread_f1,(void *)&count);
    pthread_create(&tid2,NULL,thread_f2,(void *)&count);


    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);


    return (0);

}


void * thread_f1(void * arguments){

    for(int i=0;i<3 ;i ++){
    pthread_mutex_lock(&mtid);
     for(int j=0;j<10 ;j ++){
        printf("thread1\n"); 
 
    }
    pthread_cond_signal(&cond1);
    if(i<2){pthread_cond_wait(&cond2,&mtid);}
    pthread_mutex_unlock(&mtid);      
    }
    //pthread_exit(NULL); 

    
}

void * thread_f2(void * arguments){

    for(int i=0;i<6 ;i ++){
    pthread_mutex_lock(&mtid);
     for(int j=0;j<5 ;j ++){
        printf("thread2\n"); 
 
    }
    pthread_cond_signal(&cond2);
    if(i<2){pthread_cond_wait(&cond1,&mtid);}
    pthread_mutex_unlock(&mtid);      
    }


    //pthread_exit(NULL); 

    
}




