#include<stdio.h>
#include<stdbool.h>
#define maxN 30
#define MAXCANDIDATES 5
#define T0 -1
#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5
typedef struct Value{
    int id;
    double value;
    int processor;
}Value;

int count=0;
int Processor[MAXCANDIDATES+1]={T0, T1, T2, T3, T4, T5};

bool finished = false;
int count;
Value V[maxN+1];        // value of C/T

bool is_a_solution(int a[],int k, int n);
void process_solution(int a[], int k);
void construct_candidates(int a[], int k, int c[], int* ncandidates);
void backtrack(int a[], int k, int n);
void bubbleSort(Value arr[], int n);
void bubbleSort_Des(Value arr[], int n);
void Processor_Mapping();

int main(){
    Processor_Mapping();
    return 0;
}

void backtrack(int a[], int k, int n){
    count++;
    int c[MAXCANDIDATES];       //candidates for next position
    int ncandidates=0;            //next position candidate count
    if(is_a_solution(a,k,n))
        process_solution(a,k);
    else{
        k=k+1;
        construct_candidates(a, k, c, &ncandidates);
        for(int i=0;i<ncandidates; i++){
            a[k]=c[i];
            backtrack(a,k,n);
            if(finished) return;    //terminate early
        }
    }
}

bool is_a_solution(int a[], int k, int n){
    return (k==n);
}

void process_solution(int a[], int k){    
    for(int i=1; i<=k; i++){
        for(int j=1; j<=k; j++){
            if(V[j].id==i) printf("%d ",a[j]);
        }
    }
    finished=true;
}

void construct_candidates(int a[], int k, int c[], int* ncandidates){
    Value sum[MAXCANDIDATES+1];
    for(int i=1; i<=MAXCANDIDATES; i++){
        sum[i].id=i;
        sum[i].value=0;
    }

    for(int i=1; i<k; i++){
        for(int j=1; j<=MAXCANDIDATES; j++){
            if(a[i]==Processor[j]) sum[j].value+=V[i].value;
        }
    }

    // sort the Sum 오름차순
    bubbleSort(sum, MAXCANDIDATES);


    for(int i=1; i<=MAXCANDIDATES; i++){
        if(sum[i].value+V[k].value<=1) c[(*ncandidates)++]=Processor[sum[i].id];
    }

}
void bubbleSort(Value arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 1; j < n-i; j++) {
            if (arr[j].value > arr[j+1].value) {
                Value temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void bubbleSort_Des(Value arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 1; j < n-i; j++) {
            if (arr[j].value < arr[j+1].value) {
                Value temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void Processor_Mapping(){
    int n;
    int T[maxN+1];
    int C[maxN+1];
    int a[maxN+1];
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&T[i], &C[i]);
        V[i].value=(double)C[i]/T[i];
        V[i].id=i;
    }

    bubbleSort(V,n);
    backtrack(a, 0, n);
    printf("\ncount:%d\n",count);
}



//testcase
/*
10
100 30
1000 20
5 1
9 8
8 4
57 36
32 17
5 2
6 3
7 3


second test case
30
1000 200
1000 310
1000 200
1000 190
1000 190
1000 200
1000 160
1000 180
1000 190
1000 200
1000 200
1000 210
1000 190
1000 200
1000 190
1000 200
1000 200
1000 190
1000 199
1000 200
1000 110
1000 180
1000 190
1000 170
1000 90
1000 50
1000 10
1000 10
1000 101
1000 90

third test case
15
1000 20
1000 110
1000 120
1000 130
1000 200
1000 220
1000 250
1000 300
1000 400
1000 440
1000 450
1000 460
1000 500
1000 530
1000 540


4th test case
20
1000 400
1000 180
1000 140
1000 435
1000 400
1000 120
1000 10
1000 275
1000 530
1000 540
1000 440
1000 450
1000 130
1000 220
1000 460
1000 10
1000 10
1000 10
1000 200
1000 10

5th test case
25
1000 200
1000 310
1000 200
1000 290
1000 190
1000 200
1000 160
1000 190
1000 240
1000 200
1000 200
1000 210
1000 190
1000 200
1000 190
1000 200
1000 200
1000 190
1000 199
1000 200
1000 110
1000 180
1000 190
1000 170
1000 190

*/