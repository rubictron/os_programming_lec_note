#include <stdio.h>


int main()
{
int sum = 0;
for(int i = 21; i< 912 ; i+=3){
    
    sum+= i;
}

int sum2 = 0;
int i = 21;
while(i<912){

        sum2 += i;

    i+=3;
}

 printf("from for loop %d \n",sum);
 printf("from while loop %d \n",sum2);
   return 0;
}