#include <stdio.h>
#include <stdlib.h>
 
 
int main()
{
    
    int min, max, a, sum, x, math, dif, last;
    math=0;
    dif=1;
    printf(" enter  x\n");
    scanf("%d",&x); 
    printf("Enter number from low to high\nFor Escape enter low number\n");
    //printf("number:");
    scanf("%d",&a);
    if (a==x) math++;   
    min = max = sum = last =a;
    while (a>=max)
    {           
        //printf("number:");
        scanf("%d",&a);
        if (a<max) 
        {          
           puts("Last number low, end of programm");
           continue;
        }
        sum=sum+a;            
        if (a==x) math++;
        if (a>last) dif++;
        max=last=a;
    }
    printf("summa=%d\n",sum);
    printf("min=%d\nmax=%d\n",min,max);
    printf("matches with x=%d is %d \n",x,math);
    printf("use different numbers is %d\n",dif);
    system("pause");
    return 0;
}