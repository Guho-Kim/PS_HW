#include<stdio.h>
#include<stdbool.h>
#define prohibition -9999
#define maxN 10
#define right 0
#define down 1
#define MAXCANDIDATES 2
#define NMAX 20
typedef int data;
typedef struct index{
    int row;
    int col;
}Index;
int solution_count;
int minSum=9999;
bool finished(int a[],int k,int numRight, int numDown);
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
-3 19 -3 89 -8 0 20 10 10 10
33 -4 20 30 11 0 -5 10 10 10
50 10 10 40 20 30 -1 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10
10 10 10 10 10 10 10 10 10 10

*/

//input is n;
//input2 is depth
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
            if(finished(a,k,numRight,numDown)) continue;    //terminate early
            backtrack(a,k,input,arr, path, index, numRight, numDown);
        }
    }
}

bool finished(int a[],int k,int numRight, int numDown){
    int countRight =0, countDown=0;
    for(int i=1; i<=k; i++){
        if(a[i]==right) countRight++;
        else countDown++;
    }
    if(countRight>numRight || countDown >numDown){
        // printf("I cutted since countRight and countDown are %d, %d\n",countRight, countDown);
        // for(int i=1; i<=k; i++){
        //     if(a[i]==right) printf("→");
        //     else printf("↓");
        // }
        // printf("\n");
        return true;
    } 
    else{
        // printf("I didn't cut since countRight and countDown are %d, %d\n",countRight, countDown);
        return false;
    }

}
void findWeight(Index index[], int numRight, int numDown){
    int n=numDown+numRight;
    int path[20];
    int row=index[0].row;
    int col=index[0].col;
    //Bring the map
    int arr[maxN][maxN];
    for(int i=0; i<maxN; i++){
        for(int j=0; j<maxN; j++){
            scanf("%d",&arr[i][j]);
        }
    }
    int a[NMAX];        //solution vector
    a[0]=0;
    solution_count=0;
    backtrack(a,0,n,arr, path, index, numRight, numDown);
    // printf("n=%d    solution_count=%d\n",n,solution_count);

    minSum+=arr[row-1][col-1];
    printf("%d\n",minSum);
    printf("%d %d\n",row,col);

    for(int i=1; i<=n; i++){
        if(path[i]==right){
            col++;
        }
        else{
            row++;
        }

        printf("%d %d\n",row, col);
    }

}
bool is_a_solution(int a[],int k, int n){
    return (k==n);
}
void process_solution(int a[], int k, data input, int arr[][maxN], int path[], Index index[]){    
    solution_count++;
    int sum=0;
    int condition[20];
    int row=index[0].row;
    int col=index[0].col;
    condition[0]=arr[row-1][col-1];
    //check the condition    
    for(int i=1; i<=k; i++){
        if(a[i]==right){
            sum += arr[row-1][++col-1];
            // printf("→ ");
        } 
        else if(a[i]==down){
            sum += arr[++row-1][col-1];
            // printf("↓ ");
        } 
        condition[i]=arr[row-1][col-1];
    }
    for(int i=0; i<=k; i++){
        if(condition[i]==prohibition) return;
    }
    for(int i=0; i<k; i++){
        if(condition[i]==0 && condition[i+1]==0) return;
    }
        

    // printf("\n");
    // printf("process Success and sum is %d\n",sum);
    //sum값이 작은 걸 찾아야 함.
    // for(int i=1; i<=k; i++){
    //     if(a[i]==right) printf("→");
    //     else printf("↓");
    // }
    // printf("\n");


    if(sum<minSum){
        minSum=sum;
        for(int i=1; i<=k; i++){
            path[i]=a[i];
        }
    }


}

void construct_candidates(int a[], int k, int n, int c[], int* ncandidates){
    c[0]=right;     // Move to right
    c[1]=down;      // move to down
    *ncandidates=2;
}

int main(){
    Index index[2];
    int arr[maxN][maxN];
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