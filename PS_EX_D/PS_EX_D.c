#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#define MAXCANDIDATES 64
#define NMAX 64
typedef int data;
bool finished = false;          //found all solutions yet?
int solution_count;
void process_solution(int a[], int k, data input);
bool is_a_solution(int a[],int k, int n);
void construct_candidates(int a[], int k, int n, int c[], int* ncandidates);
void backtrack(int a[], int k, data input, data input2);
void nbishop(int n, int k);


int main(){
    int n,k;
    scanf("%d %d",&n, &k);
    if(n==0 && k==0) return 0;
    else if((n>=1 && n <=8) && (k>=0 && k <= n*n)) nbishop(n,k);
    else printf("out of range");
    return 0;
}

//input is n;
//input2 is depth
void backtrack(int a[], int k, data input, data input2){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k,input2))
        process_solution(a,k,input2);
    else{
        k=k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            backtrack(a,k,input,input2);
            if(finished) return;    //terminate early
        }
    }
}
void nbishop(int n, int k){
    int a[NMAX];        //solution vector
    a[0]=0;
    solution_count=0;
    backtrack(a,0,n,k);
    printf("n=%d, k=%d    solution_count=%d\n",n,k,solution_count);
}

bool is_a_solution(int a[],int k, int n){
    return (k==n);
}
void process_solution(int a[], int k, data input){    
    solution_count++;
}

void construct_candidates(int a[], int k, int n, int c[], int* ncandidates){
    int i, j;               //counters
    bool leagal_move;       //might the move be legal?
    int row, col;
    
    *ncandidates=0;
    for(i=a[k-1]+1; i<=n*n; i++){
        row=(i-1)/n+1;
        col=(i-1)%n+1;

        leagal_move=true;
        for(j=1;j<k;j++){
            if(abs((a[j]-1)/n+1 - row) == abs((a[j]-1)%n+1 - col))//diagonal threat
            {
                leagal_move=false;
            }  
        }
        if(leagal_move==true){
            c[*ncandidates]=i;
            (*ncandidates)++;
        }

    }
}
