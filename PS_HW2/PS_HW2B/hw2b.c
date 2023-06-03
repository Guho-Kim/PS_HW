/*
    2023-05-31
    과제 제출에 틀린 부분 수정
*/


#include<stdio.h>
#include <stdlib.h>
#define minimum 0
#define maximum 1
int A,B,C,D;
void makeMatrix(char Matrix[][20]);
void showMatrix(char Matrix[][20]);
void showScore(char Matrix[][20]);


int main(){
    char Matrix[20][20];
    makeMatrix(Matrix);
    showMatrix(Matrix);
    showScore(Matrix);
    return 0;
}



void showMatrix(char Matrix[][20]){
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            printf("%c",Matrix[i][j]);
        }
        printf("\n");
    }

}

void makeMatrix(char Matrix[][20]){
    scanf("%d %d %d %d",&A, &B, &C, &D); 
    //초기화
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            if(i==j) Matrix[i][j]='X';
            else Matrix[i][j]='T';
        }
    }

    if(D==maximum){
        for(int i=0; i<C;i++){
            for(int j=C;j<20;j++){
                Matrix[i][j]='W';
                Matrix[j][i]='L';
            }
        }
    }
    else if(D==minimum){
        for(int i=0; i<C;i++){
            for(int j=C;j<20;j++){
                Matrix[i][j]='L';
                Matrix[j][i]='W';
            }
        }
    }

    if(A>2*B){
        for(int i=0; i<C; i++){
            for(int j=i+1; j<i+1+(C-1)/2; j++){
                if(j>C-1){
                    Matrix[i][j-C]='W';
                    Matrix[j-C][i]='L';
                }
                else{
                    Matrix[i][j]='W';
                    Matrix[j][i]='L';
                }
            }
        }
    }
}

void showScore(char Matrix[][20]){
    int Score[20]={0};
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            if(Matrix[i][j]=='W') Score[i]+=A;
            else if(Matrix[i][j]=='T') Score[i]+=B;
        }
    }
    for(int i=0; i<20; i++){
        printf("%d : %d\n", i+1, Score[i]);
    }
}

