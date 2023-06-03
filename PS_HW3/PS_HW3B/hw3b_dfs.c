//example of input
/*
2 3 5 6
10 20 -5 0 30 40
-1 20 55 0 -1 -2
-3 19 0 89 -9999 10
33 -4 20 30 11 -9999
50 10 10 40 -20 30
10 -10 0 -10 10 10

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

#define ROWS 6
#define COLS 6
#define INFINITE 99999
#define PROHIBITION -9999
typedef struct Coor{
    int row;
    int col;
}Coor;

int map[ROWS+1][COLS+1];
bool visited[ROWS+1][COLS+1];
int min_weight=INFINITE;
int path_size;
int min_path_size;
int count_zero;
Coor start;
Coor end;
Coor path[ROWS*COLS+1];
Coor min_path[ROWS*COLS+1];
int dir1[4]={0,1,0,-1};
int dir2[4]={1,0,-1,0};

void dfs(Coor curr, int weight){
    Coor next;
    if(curr.row == end.row && curr.col == end.col){
        if(weight < min_weight){
            min_weight=weight;
            min_path_size=path_size;
            for(int i=0; i<path_size; i++){
                min_path[i]=path[i];
            }
        }
        return;
    }
    for(int i=0; i<4; i++){
        next=curr;
        next.row+=dir1[i];
        next.col+=dir2[i];

        if(!(1<=next.row && next.row<=ROWS && 1<=next.col && next.col<=COLS ) ||
         visited[next.row][next.col] || map[next.row][next.col]==PROHIBITION){
            continue;
        }
        else if(map[next.row][next.col]==0){
            bool isZero = false;
            for(int j=0; j<path_size; j++){
                if(map[path[j].row][path[j].col]==0) isZero = true;
            }
            if(isZero) continue;
        }
        visited[next.row][next.col]=true;
        path[path_size].row=next.row;
        path[path_size].col=next.col;
        path_size++;
        dfs(next, weight+map[next.row][next.col]);
        visited[next.row][next.col] = false;
        path_size--;
    }

}

int main(){
    scanf("%d %d",&start.row, &start.col);
    scanf("%d %d",&end.row, &end.col);

    for(int i=1; i<=ROWS; i++){
        for(int j=1; j<=COLS; j++){
            scanf("%d", &map[i][j]);
        }
    }

    count_zero=0;
    path[0]=start;
    path_size=1;
    
    dfs(start, map[start.row][start.col]);
    printf("%d\n",min_weight);
    for(int i=0; i<min_path_size; i++){
        printf("%d %d\n", min_path[i].row, min_path[i].col);
    }
    
    return 0;
}