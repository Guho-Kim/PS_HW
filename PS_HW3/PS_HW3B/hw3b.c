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
bool finished(int a[],int k,Index index[]);
void findWeight(Index index[]);
bool is_a_solution(int a[],int k, Index index[]);
void process_solution(int a[], int k, int arr[][maxN], int path[], Index index[]);
void construct_candidates(int a[], int k, int c[], int* ncandidates,Index index[]);
void backtrack(int a[], int k, int arr[][maxN], int path[], Index index[]);
Index getCurrentPosition(int a[], int k,Index index[]);




//example of input
/*
2 3 5 6
10 20 -5 -4 30 40
-1 20 55 15 -1 -2
-3 19 -3 89 -8 0
33 -4 20 30 11 0
50 10 10 40 20 30
10 10 10 10 10 10

*/

//input is n;
//input2 is depth
void backtrack(int a[], int k, int arr[][maxN], int path[], Index index[]){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k,index))
        process_solution(a,k,index,arr, path, index);
    else{
        k=k+1;
        construct_candidates(a,k,c,&ncandidates,index);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            if(finished(a,k,index)) continue;    //terminate early
            backtrack(a,k,arr, path, index);
        }
    }
}

bool finished(int a[],int k,Index index[]){
    /*
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
    */

}
void findWeight(Index index[]){
    int path[maxPath];
    int row=index[0].row;
    int col=index[0].col;
    //Bring the map
    int arr[maxN][maxN];
    for(int i=1; i<=6; i++){
        for(int j=1; j<=6; j++){
            scanf("%d",&arr[i][j]);
        }
    }
    int a[maxPath];        //solution vector
    a[0]=0;
    solution_count=0;
    backtrack(a,0,arr, path, index);
    // printf("n=%d    solution_count=%d\n",n,solution_count);

    minSum+=arr[row][col];
    printf("%d\n",minSum);
    printf("%d %d\n",row,col);

    for(int i=1; i<maxPath; i++){
        if(path[i]==left){
            col--;
        }
        else if(path[i]==right){
            col++;
        }
        else if(path[i]==up){
            row--;
        }
        else if(path[i]==down){
            row++;
        }
        printf("%d %d\n",row, col);
    }

}
bool is_a_solution(int a[],int k, Index index[]){
    Index val;
    val=getCurrentPosition(a,k,index);
    return (index[1].row==val.row && index[1].col==val.col);

}

void process_solution(int a[], int k, int arr[][maxN], int path[], Index index[]){    
    solution_count++;
    int sum=0;
    int condition[20];
    int row=index[0].row;
    int col=index[0].col;
    condition[0]=arr[row][col];
    //check the condition    
    for(int i=1; i<=k; i++){
        if(a[i]==left){
            sum+= arr[row][--col];
            // printf("← ");
        }
        else if(a[i]==right){
            sum += arr[row][++col];
            // printf("→ ");
        } 
        else if(a[i]==up){
            sum += arr[--row][col];
            // printf("↑ ");
        }
        else if(a[i]==down){
            sum += arr[++row][col];
            // printf("↓ ");
        }
        condition[i]=arr[row][col];
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

void construct_candidates(int a[], int k, int c[], int* ncandidates,Index index[]){
    *ncandidates=0;
    //a를 받았으니까, 초기 위치에서 어디로 갈 지에 대한 mark 조사
    int row=index[0].row;
    int col=index[0].col;

    int mark[8][8]={0};
    mark[row][col]=1;
    //mark하고, 직전 row와 col 맞춰주기.
    for(int i=1; i<k;i++){
        switch (a[i])
        {
        case left:
            row--;
            break;
        case right:
            row++;
            break;
        case up:
            col--;
            break;
        case down:
            col++;
            break;
        default:
            break;
        }
        mark[row][col]=1;
    }


    //직전까지 왔으니까 이제 k-depth에 넣을 친구 이거 넣을만 한 거 맞는지 확인후 넣기
    //4가지 케이스 만드는 거임

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
Index getCurrentPosition(int a[], int k,Index index[]){
    Index val;
    val.row=index[0].row;
    val.col=index[0].col;

    for(int i=1; i<=k; i++){
        if(a[i]==left) val.col--;
        else if(a[i]==right) val.col++;
        else if(a[i]==up) val.row--;
        else if(a[i]==down) val.row++;
    }
    return val;
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