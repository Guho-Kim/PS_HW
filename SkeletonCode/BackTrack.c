#include<stdio.h>
#include<stdbool.h>
#define maxN 8
#define MAXCANDIDATES 4
typedef int data;
bool finished = false;
bool is_a_solution(int a[],int k, int n);
void process_solution(int a[], int k);
void construct_candidates(int a[], int k, data inpit, int c[], int* ncandidates);
void backtrack(int a[], int k, data input);




void backtrack(int a[], int k, data input){
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates;            //next position candidate count
    int i;                      //counter

    if(is_a_solution(a,k,input))
        process_solution(a,k,input);
    else{
        k=k+1;
        construct_candidates(a,k,input, c, &ncandidates);
        for(i=0;i<ncandidates; i++){
            a[k]=c[i];
            backtrack(a,k,input);
            if(finished) return;    //terminate early
        }
    }
}


bool is_a_solution(int a[],int k, int n){
    return (k==n);
}

void process_solution(int a[], int k){    
    
    for(int i=0; i<=k;i++){
        if(a[i]==true) printf("%d\n", i);
    }

}

void construct_candidates(int a[], int k, int n, int c[], int* ncandidates){
    c[0] = true;
    c[1] = false;
    *ncandidates = 2;

}

int main(){

    return 0;
}