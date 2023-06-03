#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#define MAXCANDIDATES 64
#define NMAX 64
typedef int data;
bool finished = false;          //found all solutions yet?
int solution_count;
void process_solution();
bool is_a_solution(int n, int k);
void construct_candidates(int a[], int size, int k, int c[], int* ncandidates);
void backtrack(int a[], int size, int numBishop, int k);
void nbishop(int n, int k);


int main(){
    int size, numBishop;
    while (true){
        scanf("%d %d",&size, &numBishop);
        if(size==0 && numBishop==0) return 0;
        else if((size>=1 && size <=8) && (numBishop>=0 && numBishop <= size*size)) nbishop(size,numBishop);
        else printf("out of range");

    }
    return 0;
}

void nbishop(int size, int numBishop){
    int a[NMAX];        //solution vector
    a[0]=0;
    solution_count=0;
    backtrack(a, size, numBishop, 0);
    printf("solution_count=%d\n",solution_count);
}

void backtrack(int a[], int size, int numBiship, int k){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(numBiship, k))
        process_solution();
    else{
        k=k+1;
        construct_candidates(a, size, k, c, &ncandidates);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            backtrack(a, size, numBiship, k);
            if(finished) return;    //terminate early
        }
    }
}

bool is_a_solution(int numBiship, int k){
    return (numBiship==k);
}
void process_solution(){    
    solution_count++;
}

void construct_candidates(int a[], int size, int k, int c[], int* ncandidates){
    bool leagal_move;       //might the move be legal?
    int row, col;
    
    *ncandidates=0;
    for(int i=a[k-1]+1; i<=size*size; i++){
        row=(i-1)/size+1;
        col=(i-1)%size+1;

        leagal_move=true;
        for(int j=1;j<k;j++){
            if(abs((a[j]-1)/size+1 - row) == abs((a[j]-1)%size+1 - col))//diagonal threat
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
