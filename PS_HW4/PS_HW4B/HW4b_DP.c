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
*/

#include<stdio.h>
#define MAXN 30         // max number of items
#define CAPACITY 1000          // max numer of procecss
#define min(a,b) (a>b) ? a : b

int items[MAXN];
int item_size;

void KnapSack(int W[], int n){
    int K[n+1][CAPACITY+1];
    int i, j;
    //초기화
    for(i=0; i<=n; i++) K[i][0] = 0;
    for(j=0; j<=CAPACITY; j++) K[0][j] = 0;

    // K[i][j] : j용량의 배낭에 i번째까지의 아이템을 넣으려고 했을 때의 최대 가치(무게).
    for(i=1; i<=n; i++){
        for(j=0; j<=CAPACITY; j++){
            if(W[i]>j){
                K[i][j]=K[i-1][j];
            }
            else{
                K[i][j]=min(K[i-1][j], W[i]+K[i-1][j-W[i]]);
            }

        }
    }


    //item 추출
    i=n;
    j=CAPACITY;
    item_size=0;
    while(i!=0){
        if(K[i][j] != K[i-1][j]){   //i번째 아이템이 가방에 들어갔다면
            j-=W[i];
            items[item_size++]=i;
        }
        i--;
    }

}

int main(){
    int n;           // n : number of items
    int C[MAXN+1], T[MAXN+1];
    int V[MAXN+1], W[MAXN+1];
    int Process[5]={0};
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %d", &T[i], &C[i]);
        W[i+1] = C[i]*1000/T[i];
    }

    for(int i=0; i<5; i++){
        KnapSack(W,n);
        for(int j=0; j<item_size; j++){
            printf("%dth items %d in %d Processor\n",items[j], W[items[j]], i+1);
            Process[i]+=W[items[j]];
            W[items[j]]=0;
        }
    }



    // for(int j=0; j<=MAXC*1000; j+=1000){
    //     printf("%d\t:",j);
    //     for(int i=0; i<=n; i++){
    //         printf("%d ",K[i][j]);
    //     }
    //     printf("\n");
    // }

    int sum=0;    
    for(int i = 0; i<5; i++){
        printf("%dth processor value is %d\n",i+1, Process[i]);
    }
    // printf("sum = %d",sum);

    return 0;
}