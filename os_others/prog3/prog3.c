#include <stdio.h>

int findMax(int n[]){

    int m = n[0];
    size_t length = sizeof(n) / sizeof(n[0]); 
    int s = (int) length;

    for(int i=0; i< s;i++){
         if(n[i] > m)
            m = n[i];
    }

    return m;

}


int main() {

int nums[10];

for(int i=0;i<10;i++){
    scanf("%d",&nums[i]);
}

printf("max num is =%d \n",findMax(nums));

   return 0; 
}


