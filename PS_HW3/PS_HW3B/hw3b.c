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
#include<stdio.h>
#include<stdbool.h>
#define left 1
#define right 2
#define up 3
#define down 4
#define prohibition -9999
#define maxPath 40
#define maxSize 8
#define MAXCANDIDATES 4
typedef int data;
typedef struct index{
    int row;
    int col;
}Index;
Index index[2];
int map[maxSize][maxSize];
int path[maxPath];
int solution_count;
int minSum=9999;

bool finished(int a[],int k);
void findWeight();
bool is_a_solution(int a[],int k);
void process_solution(int a[], int k);
void construct_candidates(int a[], int k, int c[], int* ncandidates);
void backtrack(int a[], int k);

int main(){
    findWeight();

    return 0;
}
void findWeight(){
    //Starting point and destination point
    for(int i=0;i<2;i++){
        scanf("%d",&index[i].row);
        scanf("%d",&index[i].col);
    }

    int row=index[0].row, col=index[0].col;
    int a[maxPath];        //solution vector


    for(int i=1; i<=6; i++){
        for(int j=1; j<=6; j++){
            scanf("%d",&map[i][j]);
        }   
    }

    a[0]=0;
    solution_count=0;
    backtrack(a, 0);
    
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


void backtrack(int a[], int k){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k))
        process_solution(a,k);
    else{
        k=k+1;
        construct_candidates(a,k,c,&ncandidates);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            if(finished(a,k)) continue;    //terminate early
            backtrack(a,k);
        }
    }
}

bool finished(int a[],int k){
    int condition[40];
    int row=index[0].row;
    int col=index[0].col;
    int z_count=0;
    condition[0]=map[row][col];

    //check the condition    
    for(int i=1; i<=k; i++){
        if(a[i]==left) col--;
        else if(a[i]==right) col++;
        else if(a[i]==up) row--;
        else if(a[i]==down) row++;
        //out of range
        if(!(1<=row && row<=6)) return true; 
        else if(!(1<=col && col<=6)) return true;
        condition[i]=map[row][col];
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

bool is_a_solution(int a[],int k){
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

void process_solution(int a[], int k){    
    solution_count++;
    int sum;
    int row=index[0].row;
    int col=index[0].col;
    sum=map[row][col];
    
    for(int i=1; i<=k; i++){
        if(a[i]==left) sum+= map[row][--col];
        else if(a[i]==right) sum += map[row][++col];
        else if(a[i]==up) sum += map[--row][col];
        else if(a[i]==down) sum += map[++row][col];
    }

    if(sum<minSum){
        minSum=sum;
        for(int i=1; i<=k; i++) path[i]=a[i];
    }
}

void construct_candidates(int a[], int k, int c[], int* ncandidates){
    /*finished에서 내가 잘랐던 것들을 construct에서 못 만들게 해야지 효과적인 것임.*/
    /*prohibition도 finished에 있을 게 아님.*/
    /*more than two of zero도 construct에서 하는 게 낳을 거임. 뒤에 트리를 더 만드는 것보다는.*/
    /*
        prohibition은 통제하기 쉬움.
        multiple zero는 parameter로 갯수를 받아서? or 0이 들어왔을 때만, 0의 개수 체크해보는 for문 실행하는 것도 ㄱㅊ
    
    
    */

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

