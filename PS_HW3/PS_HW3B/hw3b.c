#include<stdio.h>
#include<stdbool.h>
#define left 1
#define right 2
#define up 3
#define down 4
#define prohibition -9999
#define maxPath 40
#define maxN 8
#define MAXCANDIDATES 4
typedef int data;
typedef struct index{
    int row;
    int col;
}Index;
int solution_count;
int minSum=9999;
bool finished(int a[],int k,int arr[][maxN],Index index[]);
void findWeight(Index index[]);
bool is_a_solution(int a[],int k, Index index[]);
void process_solution(int a[], int k, int arr[][maxN], int path[], Index index[]);
void construct_candidates(int a[], int k, int c[], int* ncandidates,Index index[]);
void backtrack(int a[], int k, int arr[][maxN], int path[], Index index[]);




//example of input
/*
2 2 5 5
20 -5 -4 30 40 50
20 55 15 -1 -2 40
19 -3 89 -8 10 20
-4 20 30 11 -5 -5
10 10 40 20 30 -1
20 20 20 20 20 20
*/

void backtrack(int a[], int k, int arr[][maxN], int path[], Index index[]){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k,index))
        process_solution(a,k,arr, path, index);
    else{
        k=k+1;
        construct_candidates(a,k,c,&ncandidates,index);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            if(finished(a,k,arr,index)) continue;    //terminate early
            backtrack(a,k,arr, path, index);
        }
    }
}

bool finished(int a[],int k,int arr[][maxN],Index index[]){
    int condition[40];
    int row=index[0].row;
    int col=index[0].col;
    int z_count=0;
    condition[0]=arr[row][col];

    //check the condition    
    for(int i=1; i<=k; i++){
        if(a[i]==left) col--;
        else if(a[i]==right) col++;
        else if(a[i]==up) row--;
        else if(a[i]==down) row++;
        //out of range
        if(!(1<=row && row<=6)) return true; 
        else if(!(1<=col && col<=6)) return true;
        condition[i]=arr[row][col];
    }
    for(int i=0; i<=k; i++){
        if(condition[i]==prohibition) return true;
    }
    for(int i=0; i<=k; i++){
        if(condition[i]==0) z_count++;
    }
    if(z_count>1) return true;

    return false;

}
void findWeight(Index index[]){
    int path[maxPath], row=index[0].row, col=index[0].col;
    int arr[maxN][maxN];
    int a[maxPath];        //solution vector
    for(int i=1; i<=6; i++){
        for(int j=1; j<=6; j++){
            scanf("%d",&arr[i][j]);
    }   }
    a[0]=0;
    solution_count=0;
    backtrack(a,0,arr, path, index);
    minSum+=arr[row][col];
    printf("%d\n",minSum);
    printf("%d %d\n",row,col);
    for(int i=1; i<maxPath; i++){
        if(path[i]==left) col--;
        else if(path[i]==right) col++;
        else if(path[i]==up) row--;
        else if(path[i]==down) row++;
        printf("%d %d\n",row, col);
        if(row==index[1].row && col==index[1].col) break;
    }

}
bool is_a_solution(int a[],int k, Index index[]){
    int row=index[0].row;
    int col=index[0].col;

    for(int i=1; i<=k; i++){
        if(a[i]==left) col--;
        else if(a[i]==right) col++;
        else if(a[i]==up) row--;
        else if(a[i]==down) row++;
    }
    
    return ((index[1].row==row) && (index[1].col==col));

}

void process_solution(int a[], int k, int arr[][maxN], int path[], Index index[]){    
    solution_count++;
    int sum=0;
    int row=index[0].row;
    int col=index[0].col;
    for(int i=1; i<=k; i++){
        if(a[i]==left) sum+= arr[row][--col];
        else if(a[i]==right) sum += arr[row][++col];
        else if(a[i]==up) sum += arr[--row][col];
        else if(a[i]==down) sum += arr[++row][col];
    }

    if(sum<minSum){
        minSum=sum;
        for(int i=1; i<=k; i++) path[i]=a[i];
    }
}

void construct_candidates(int a[], int k, int c[], int* ncandidates,Index index[]){
    *ncandidates=0;
    int row=index[0].row, col=index[0].col;
    int mark[8][8]={0};
    mark[row][col]=1;
    //mark하고, 직전 row와 col 맞춰주기.
    for(int i=1; i<k;i++){
        if(a[i]==left) col--;
        else if(a[i]==right) col++;
        else if(a[i]==up) row--;
        else if(a[i]==down) row++;
        mark[row][col]=1;
    }

    //left
    if(col>1 && mark[row][col-1]!=1){
        c[*ncandidates]=left;
        (*ncandidates)++;
    }
    //right
    if(col<6 && mark[row][col+1]!=1){
        c[*ncandidates]=right;
        (*ncandidates)++;
    }
    //up
    if(row>1 && mark[row-1][col]!=1){
        c[*ncandidates]=up;
        (*ncandidates)++;
    }
    //down
    if(row<6 && mark[row+1][col]!=1){
        c[*ncandidates]=down;
        (*ncandidates)++;
    }
}

int main(){
    Index index[2];
    int arr[maxN][maxN];
    //Starting point and destination point
    for(int i=0;i<2;i++){
        scanf("%d",&index[i].row);
        scanf("%d",&index[i].col);
    }

    findWeight(index);

    return 0;
}