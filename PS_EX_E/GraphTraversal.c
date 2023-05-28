/*
    Problem Solving Lecture
    Lecture Note 9~10
    This code for Topological Sorting

*/

#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#define MAXV 10000  //number of vertices

bool isForbidden(int w[], int forbidden[][4], int n) {
    for (int i = 0; i < n; i++) {
        if (w[3] == forbidden[i][3] && w[2] == forbidden[i][2] && w[1] == forbidden[i][1] && w[0] == forbidden[i][0]) {
            return true;
        }
    }
    return false;
}

int make_value(int arr[]){
    int value=0;
    int j=1;
    for(int i=0; i<4; i++){
        value+=arr[i]*j;
        j*=10;
    }
    return value;
}
void make_arr(int arr[], int value){
    arr[3]=(value)/1000;
    arr[2]=(value%1000)/100;
    arr[1]=(value%100)/10;
    arr[0]=(value%10);
}



int bfs(int start[], int dest[], int forbidden[][4], int n){
    int depth[MAXV];
    for(int i=0; i<MAXV; i++) depth[i]=0;
    Queue queue;
    initQueue(&queue);
    bool visited[10][10][10][10]={0};
    int curr[4];
    int count=0;
    int curr_val;
    for(int i=0; i<4; i++) curr[i]=start[i];

    enqueue(&queue, make_value(start));
    visited[start[3]][start[2]][start[1]][start[0]]=true;

    while(isEmpty(&queue)==false){
        curr_val=dequeue(&queue);   // value of pop
        make_arr(curr,curr_val);    // make poped value to arr

        //finish
        if (curr[3] == dest[3] && curr[2] == dest[2] && curr[1] == dest[1] && curr[0] == dest[0]) 
            return depth[curr_val];

        for (int i = 0; i < 4; i++) {
            int next[4];
            // rotate to right
            for(int j=0; j<4; j++) next[j]=curr[j];
            next[i] = (next[i] + 1) % 10;
            if (!visited[next[3]][next[2]][next[1]][next[0]] && !isForbidden(next, forbidden, n)) {
                enqueue(&queue, make_value(next));
                depth[make_value(next)]=depth[make_value(curr)]+1;
                visited[next[3]][next[2]][next[1]][next[0]] = true;
            }
            // rotate to left
            for(int j=0; j<4; j++) next[j]=curr[j];
            next[i] = (next[i] + 9) % 10;
            if (!visited[next[3]][next[2]][next[1]][next[0]] && !isForbidden(next, forbidden, n)) {
                enqueue(&queue, make_value(next));
                depth[make_value(next)]=depth[make_value(curr)]+1;
                visited[next[3]][next[2]][next[1]][next[0]] = true;
            }
        }
    }
    // impossible
    return -1;
}

/*
test case
2

8 0 5 6
6 5 0 8
5
8 0 5 7
8 0 4 7
5 5 0 8
7 5 0 8
6 4 0 8

1 1 1 1
2 2 2 2
8
1 1 1 2
1 1 1 0
1 1 2 1
1 1 0 1
1 2 1 1
1 0 1 1
2 1 1 1
0 1 1 1

*/
int main(){
    int start[4];
    int dest[4];
    int forbidden[MAXV][4];
    int loop;       // how many times?
    int n;          // how many forbidden?

    scanf("%d", &loop);
    for(int i=0; i<loop; i++){
        for(int j=0; j<MAXV; j++){
            for(int k=0; k<4; k++){
                forbidden[j][k]=0;
            }
        }

        // getting start and dest numbers 
        scanf("%d%d%d%d",&start[3],&start[2],&start[1],&start[0]);
        scanf("%d%d%d%d",&dest[3],&dest[2],&dest[1],&dest[0]);

        scanf("%d", &n);
        // make forbidden cases
        for(int i=0; i<n; i++){
            scanf("%d%d%d%d",&forbidden[i][3],&forbidden[i][2],&forbidden[i][1],&forbidden[i][0]);
        }
        printf("%d\n",bfs(start, dest, forbidden, n));
    }

    return 0;
}

