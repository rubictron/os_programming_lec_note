#include <stdio.h>

long unsigned factorial( int num){

    if(num == 1){
        return 1;
    }
    else{
        return num * factorial(num-1);
    }   
}


int main() {

    int a=0;

    scanf("%d", &a);

    printf("factorial of is = %ld \n",factorial(a));
    
    return 0;
}