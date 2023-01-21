#include <stdio.h>


int main()
{
char gender;

printf("enter your gender");

scanf("%c", &gender);

if(gender == 'm' || gender== 'M'){
    printf(" You are Male");
}
else if(gender == 'f' || gender == 'F'){
    printf(" you are Female");
    }
else{
    printf("invalid input");
}

   return 0;
}