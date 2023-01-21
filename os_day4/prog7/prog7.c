#include <stdio.h>


int main()
{
char operater;
float num1,num2,ans;

printf("enter first leter of your operater");

scanf("%c", &operater);

printf("enter two numbers for calculation");

scanf("%f %f", &num1,&num2);

if(64 < operater && operater < 91){operater = operater + 32; }

switch(operater){

    case ('a'):
        ans = num1 + num2;
        break;
    case ('s'):
        ans = num1 - num2;
        break;
    case ('d'):
        if(num2 == 0) {
            printf("invalid number\n");
            return 0;
        }
        ans = num1 / num2;
        break;
    case ('m'):
        ans = num1 * num2;
        break;  
    default:
        printf("invalid input\n");
        return 0;
}

printf("Answer = %.3f \n",ans);

   return 0;
}