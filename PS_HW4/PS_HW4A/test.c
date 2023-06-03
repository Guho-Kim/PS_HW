#include<stdio.h>
int main(){

    int n=1;
    switch (n)
    {
    case 1:
    
        printf("n is %d\n",n);
        n=2;

        
    case 2:
        printf("n is %d\n",n);
        n=1;
        
    }


    return 0;
}