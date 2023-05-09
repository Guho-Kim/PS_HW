/*
    Problem Solving Lecture
    Lecture Note 9~10
    This code for Topological Sorting

*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue.h>
// #include <sys/queue.h>

#define MAXV        100                 /* maximum number of vertices */
#define MAXDEGREE   50                  /* maximum vertex outdegree */
typedef struct{
    int edges[MAXV+1][MAXDEGREE];       /* adjacency info */
    int degree[MAXV+1];                 /* outdegree of each vertex */
    int nvertices;                      /* number of vertices in graph */
    int nedges;                         /* number of edges in graph */
} graph;

//making indegrees
compute_indegrees(graph *g, int in[]){
    for(int i=1; i<=g->nvertices; i++) in[i]=0;

    for(int i=1; i<g->nvertices; i++){
        for(int j=0; j<g->degree[i]; j++){
            in[g->degree[i]]++;
        }
    }
}


read_graph(graph *g, bool directed){
    int m;                              /* number of edges*/
    int x, y;                           /* vertices in dege (x,y) */

    initialize_graph(g);
    
    scanf("$d $d", &(g->nvertices), &m);

    for(int i=1; i<=m; i++){
        scanf("%d %d", &x, &y);
        insert_edge(g,x,y,directed);
    }

}

insert_edge(graph *g, int x, int y, bool directed){
    if(g->degree[x] > MAXDEGREE)
        printf("Warning: insertion(%d, %d) exceeds max degree\n",x,y);
    g->edges[x][g->degree[x]] = y;
    g->degree[x] ++;

    if (directed == false)
        insert_edge(g,y,x,true);
    else
        g->nedges++;
}

topsort(graph *g, int sorted[]){
    int indegree[MAXV];
    Queue zeroin;
    int j;
    int x,y;

    compute_indegrees(g, indegree);
    init_queue(&zeroin);
    for(int i=1; i<=g->nvertices; i++)
        if(indegree[i]==0) enqueue(&zeroin, i);
    
    j=0;
    while(isEmpty(&zeroin) == false){
        j++;
        x = dequeue(&zeroin);
        sorted[j] = x;
        for(int i=0; i<g->nvertices; i++){
            y=g->edges[x][i];
            indegree[y]--;
            if(indegree[y]==0) enqueue(&zeroin,y);
        }
    }

    if(j!=g->nvertices)
        printf("Not a DAG -- only %d vertices found\n", j);
}

int main(){
    graph g;


    return 0;
}