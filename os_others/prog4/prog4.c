#include <stdio.h>


int main() {

int n[10];

size_t length = sizeof(n) / sizeof(n[0]); 
int s = (int) length;

for(int i=0;i<s;i++){
    scanf("%d",&n[i]);
}

int temp = 0;

    

    for(int i=0; i< s;i++){
         for(int j=0;j< s-1 ;j++) {
             if(n[j] < n[j+1])
             {
                 temp = n[j];
                 n[j] = n[j+1];
                 n[j+1]=temp;

             }
         }
    }

for(int i=0;i<s;i++){
printf("%d ",n[i]);
}
printf("\n");
   return 0; 
}


