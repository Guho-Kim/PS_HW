#include<stdio.h>
#include<string.h>
#include <stdlib.h>
void b_sort(int arr[], int n){
    int temp;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++){
            if(arr[j]<arr[j+1]){
                temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

int main(){
    char Matrix[20][20];
    int Score[20];
    int A,B;
    for(int i=0; i<20; i++) Score[i]=0;

    //Win : A points, Tie : B points, Lose : 0 point
    // 0<B<A<10
    scanf("%d %d",&A, &B); 
    for(int i=0; i<20;i++) scanf("%s",&Matrix[i]);
        
    for(int i=0; i<20;i++){
        for(int j=0;j<20;j++){
            if(Matrix[i][j]=='W') Score[i]+=A;
            else if(Matrix[i][j]=='T') Score[i]+=B;
        }
    }


    b_sort(Score,20);
    for(int i=0; i<20; i++) printf("%d\n",Score[i]);

    return 0;
}