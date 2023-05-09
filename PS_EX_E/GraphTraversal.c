/*
    Problem Solving Lecture
    Lecture Note 9~10
    This code for Topological Sorting

*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue.h>

#define MAXV        10000                 /* maximum number of vertices */
#define MAXDEGREE   8                  /* maximum vertex outdegree */
typedef struct{
    int edges[MAXV+1][MAXDEGREE];       /* adjacency info */
    int degree[MAXV+1];                 /* outdegree of each vertex */
    int nvertices;                      /* number of vertices in graph */
    int nedges;                         /* number of edges in graph */
} graph;

// //making indegrees
// compute_indegrees(graph *g, int in[]){
//     for(int i=1; i<=g->nvertices; i++) in[i]=0;

//     for(int i=1; i<g->nvertices; i++){
//         for(int j=0; j<g->degree[i]; j++){
//             in[g->degree[i]]++;
//         }
//     }
// }


// make_graph(graph *g, bool directed){
//     int m;                              /* number of edges*/
//     int x, y;                           /* vertices in dege (x,y) */
//     // int arr[9][9][9][9];
//     int arr[4]={0};
//     for(int i=0; i<10; i++){
//         insert_edge(g,arr[3]+arr[2]+arr[1]+arr[0],arr[3]+arr[2]+arr[1]+arr[0] +i, false );
//     }


//     initialize_graph(g);
    
//     // scanf("$d $d", &(g->nvertices), &g->nedges);
//     g->nvertices = 0;
//     g->nedges = 0;
    
//     m=g->nedges;

//     // for(int i=1; i<=m; i++){
//     //     scanf("%d %d", &x, &y);
//     //     insert_edge(g,x,y,directed);
//     // }




// }
// initialize_graph(graph *g){
//     for(int i=0; i<MAXV+1; i++){
//         for(int j=0; j<MAXDEGREE; j++){
//             g->edges[i][j]=0;
//         }
//         g->degree[i]=0;
//     }

// }


// insert_edge(graph *g, int x, int y, bool directed){
//     if(g->degree[x] > MAXDEGREE)
//         printf("Warning: insertion(%d, %d) exceeds max degree\n",x,y);
//     g->edges[x][g->degree[x]] = y;
//     g->degree[x] ++;

//     if (directed == false)
//         insert_edge(g,y,x,true);
//     else
//         g->nedges++;
// }

// topsort(graph *g, int sorted[]){
//     int indegree[MAXV];
//     Queue zeroin;
//     int j;
//     int x,y;

//     compute_indegrees(g, indegree);
//     init_queue(&zeroin);
//     for(int i=1; i<=g->nvertices; i++)
//         if(indegree[i]==0) enqueue(&zeroin, i);
    
//     j=0;
//     while(isEmpty(&zeroin) == false){
//         j++;
//         x = dequeue(&zeroin);
//         sorted[j] = x;
//         for(int i=0; i<g->nvertices; i++){
//             y=g->edges[x][i];
//             indegree[y]--;
//             if(indegree[y]==0) enqueue(&zeroin,y);
//         }
//     }

//     if(j!=g->nvertices)
//         printf("Not a DAG -- only %d vertices found\n", j);
// }
int make_value(int arr[]){
    int value=0;
    for(int i=1; i<=1000; i*=10){
        value+=arr[i]*i;
    }
    return value;
}

int bfs(int start[], int target[], int forbidden[][4], int n){
    Queue queue;
    bool visited[10][10][10][10]={0};

    enqueue(&queue, make_value(start));
    visited[start[0]][start[1]][start[2]][start[3]]=true;

    while(isEmpty(&queue)==false){
        // if()


    }



}



int main(){
    //start == 8 0 5 6;
    //dest == 6 5 0 8;
    int start[4];
    int dest[4];
    //나중에 scanf로 변경
    start[0]=6;
    start[1]=5;
    start[2]=0;
    start[3]=8;

    dest[0]=8;
    dest[1]=0;
    dest[2]=5;
    dest[3]=6;

    return 0;
}

