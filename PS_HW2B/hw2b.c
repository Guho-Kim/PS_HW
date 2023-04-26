#include<stdio.h>
#include <stdlib.h>
    //maximum OR minimum points (D) of a team with the Cth largest scores
    //Win : A points, Tie : B points, Lose : 0 point
    //C : target ranking 1~20
    //D : 0 (min) or 1 (max)
    // 0<B<A<10
    //D=1일 경우, 만약 C=3이면 3등의 점수가 최대한 크게 해야함.
int main(){
    char Matrix[20][20];
    int Score[20];
    int A,B,C,D;
    for(int i=0; i<20; i++) Score[i]=0;
    scanf("%d %d %d %d",&A, &B, &C, &D); 
    if(D==1){
        for(int i=0; i<C;i++){
            for(int j=0;j<20;j++){
                if(i==j) Matrix[i][j]='X';
                else if(j<C) Matrix[i][j]='T';
                else Matrix[i][j]='W';
        }}
        for(int i=C; i<20;i++){
            for(int j=0;j<20;j++){
                if(i==j) Matrix[i][j]='X';
                else if(j<C) Matrix[i][j]='L';
                else Matrix[i][j]='T';
        }}
    }
    else if(D==0){
        C=21-C;
        for(int i=0; i<C;i++){
            for(int j=0;j<20;j++){
                if(i==j) Matrix[i][j]='X';
                else if(j<C) Matrix[i][j]='T';
                else Matrix[i][j]='L';
        }}
        for(int i=C; i<20;i++){
            for(int j=0;j<20;j++){
                if(i==j) Matrix[i][j]='X';
                else if(j<C) Matrix[i][j]='W';
                else Matrix[i][j]='T';
        }}
    }


    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            if(Matrix[i][j]=='W') Score[i]+=A;
            else if(Matrix[i][j]=='T') Score[i]+=B;
        }
    }

    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            printf("%c",Matrix[i][j]);
        }
        printf("\n");
    }
    
    /*
    for(int i=0; i<20; i++){
        printf("%d\n",Score[i]);
    }
    */

    return 0;
}