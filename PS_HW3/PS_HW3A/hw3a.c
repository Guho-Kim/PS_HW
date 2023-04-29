#include<stdio.h>
#include<stdbool.h>
#define prohibition -9999
#define maxN 20
#define right 1
#define down 2
#define MAXCANDIDATES 2
#define NMAX 20
typedef int data;
typedef struct index{
    int row;
    int col;
}Index;
int solution_count;
int minSum=9999;
bool finished(int a[],int k,int arr[][maxN],int numRight, int numDown,Index index[]);
void findWeight(Index index[], int numRight, int numDown);
bool is_a_solution(int a[],int k, int n);
void process_solution(int a[], int k, data input, int arr[][maxN], int path[], Index index[]);
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates);
void backtrack(int a[], int k, data input, int arr[][maxN], int path[], Index index[],int numRight, int numDown);



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

void backtrack(int a[], int k, data input, int arr[][maxN], int path[], Index index[],int numRight, int numDown){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k,input))
        process_solution(a,k,input,arr, path, index);
    else{
        k=k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            if(finished(a,k,arr,numRight,numDown,index)) continue;    //terminate early
            backtrack(a,k,input,arr, path, index, numRight, numDown);
        }
    }
}

bool finished(int a[],int k,int arr[][maxN],int numRight, int numDown, Index index[]){
    int countRight =0, countDown=0;
    int row=index[0].row, col=index[0].col, z_count=0;
    int condition[20];
    //check the boundary
    for(int i=1; i<=k; i++){
        if(a[i]==right) countRight++;
        else countDown++;
    }
    if(countRight>numRight || countDown >numDown) return true;   
    //check the condition    
    condition[0]=arr[row][col];
    for(int i=1; i<=k; i++){
        if(a[i]==right) col++;
        else if(a[i]==down) row++;
        condition[i]=arr[row][col];
    }
    for(int i=0; i<=k; i++) if(condition[i]==prohibition) return true;
    for(int i=0; i<=k; i++) if(condition[i]==0) z_count++;
    if(z_count >1) return true;
    return false;
}
void findWeight(Index index[], int numRight, int numDown){
    int n=numDown+numRight;
    int path[20];
    int row=index[0].row;
    int col=index[0].col;
    int arr[maxN][maxN];
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            scanf("%d",&arr[i][j]);
    }   }
    int a[NMAX];        //solution vector
    a[0]=0;
    solution_count=0;
    backtrack(a,0,n,arr, path, index, numRight, numDown);
    minSum+=arr[row][col];
    printf("%d\n",minSum);
    printf("%d %d\n",row,col);
    for(int i=1; i<=n; i++){
        if(path[i]==right) col++;
        else row++;
        printf("%d %d\n",row, col);
    }
}
bool is_a_solution(int a[],int k, int n){
    return (k==n);
}
void process_solution(int a[], int k, data input, int arr[][maxN], int path[], Index index[]){    
    solution_count++;
    int sum=0, row=index[0].row, col=index[0].col;
    //check the condition    
    for(int i=1; i<=k; i++){
        if(a[i]==right) sum += arr[row][++col];
        else if(a[i]==down) sum += arr[++row][col];
    }
    if(sum<minSum){
        minSum=sum;
        for(int i=1; i<=k; i++) path[i]=a[i];
    }
}

void construct_candidates(int a[], int k, int n, int c[], int* ncandidates){
    c[0]=right;     // Move to right
    c[1]=down;      // move to down
    *ncandidates=2;
}

int main(){
    Index index[2];
    int sum=0;
    int numRight, numDown;
    //Starting point and destination point
    for(int i=0;i<2;i++){
        scanf("%d",&index[i].row);
        scanf("%d",&index[i].col);
    }
    //number of moving
    numDown=index[1].row-index[0].row;
    numRight=index[1].col-index[0].col;

    findWeight(index,numRight,numDown);

    return 0;
}