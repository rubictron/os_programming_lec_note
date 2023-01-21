#include <stdio.h>



int main() {

int nums[10];
int m=nums[0];

for(int i=0;i<10;i++){
    scanf("%d",&nums[i]);
    if(nums[i]<m)
    m =nums[i];
}

printf("min num is =%d \n",m);

   return 0; 
}


