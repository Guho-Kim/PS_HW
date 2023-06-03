//example of input
/*
2 3 5 6
10 20 -5 -4 30 40 50 10 10 10
-1 20 55 15 -1 -2 40 10 10 10
-3 19 -3 89 -8 10 20 10 10 10
33 -4 20 30 11 -5 -5 10 10 10
50 10 10 40 20 30 -1 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10

*/

#include<stdio.h>
#include<stdbool.h>
#define prohibition -9999
#define maxSize 10
#define right 1
#define left 2
#define up 3
#define down 4
#define MAXCANDIDATES 2
typedef int data;
typedef struct index{
    int row;
    int col;
}Index;

Index index[2];
int solution_count;
int minSum=9999;
int map[maxSize+10][maxSize+10];
int path[20];
int numRight, numDown;
bool finished = false;

void findWeight();
bool is_a_solution(int a[],int k, int n);
void process_solution(int a[], int k, data input);
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates);
void backtrack(int a[], int k, data input);

int main(){
    findWeight();
    return 0;
}


void findWeight(){
    int n;
    int row, col;
    int a[20];        //solution vector

    //Starting point and destination point
    for(int i=0;i<2;i++){
        scanf("%d",&index[i].row);
        scanf("%d",&index[i].col);
    }
    // making map
    for(int i=1; i<=maxSize; i++)
        for(int j=1; j<=maxSize; j++)
            scanf("%d",&map[i][j]);
    

    //number of moving
    numDown=index[1].row-index[0].row;
    numRight=index[1].col-index[0].col;

    // number of total moving
    n=numDown+numRight;

    a[0]=0;
    solution_count=0;
    // backtrack ftn will make numSum
    backtrack(a,0,n);

    row = index[0].row;
    col = index[0].col;

    printf("%d\n",minSum);
    printf("%d %d\n",row,col);
    for(int i=1; i<=n; i++){
        if(path[i]==right) col++;
        else row++;
        printf("%d %d\n",row, col);
    }
    printf("solution_count is %d\n",solution_count);
}



void backtrack(int a[], int k, data input){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count

    if(is_a_solution(a,k,input))
        process_solution(a,k,input);
    else{
        k=k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for(int i=0;i<ncandidates; i++){
            a[k]=c[i];
            backtrack(a,k,input);
            if(finished) return;    //terminate early
        }
    }
}
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates){
    int countRight=0, countDown=0;
    int lastRow, lastCol;
    int numZero=0;
    *ncandidates=0;

    lastRow=index[0].row, lastCol=index[0].col;
    for(int i=1; i<k; i++){
        if(a[i]==right) lastCol++;
        else lastRow++;
    }
    
    for(int row = index[0].row; row<=lastRow; row++)
        for(int col = index[0].col; col<=lastCol; col++)
            if(map[row][col]==0) numZero++;

    if(numZero >1) return;

    if(lastCol < index[1].col && map[lastRow][lastCol+1]!=prohibition){
        c[(*ncandidates)++]=right;
    }
    if(lastRow < index[1].row && map[lastRow+1][lastCol]!=prohibition){
        c[(*ncandidates)++]=down;
    }

}

bool is_a_solution(int a[],int k, int n){
    return (k==n);
}
void process_solution(int a[], int k, data input){    
    solution_count++;
    int sum, row=index[0].row, col=index[0].col;
    
    //check the condition    
    sum=map[row][col];
    for(int i=1; i<=k; i++){
        if(a[i]==right) sum += map[row][++col];
        else if(a[i]==down) sum += map[++row][col];
    }
    if(sum<minSum){
        minSum=sum;
        for(int i=1; i<=k; i++) path[i]=a[i];
    }
}


