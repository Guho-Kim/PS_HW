#include<stdio.h>
#define NFLOORS     110         /* the building height in floors */
#define MAX_RIDERS  501          /* what is the elevator capacity? */
#define MAXINT      ~(1<<31)
#define min(i, j) ((i)<(j) ? (i) : (j))
#define abs(i) ((i)>0 ? (i) : (i*(-1)))



int stops[MAX_RIDERS];          /* what floor does everyone get off? */
int nriders;                    /* number of riders */
int nstops;                     /* number of allowable stops */
int stopped[MAX_RIDERS];        /* will be stored the stopped floors*/
int count=1;                    /* counter for stopped */

// m[i][j] is the minimum cost, when i floor is jth stop and that is last stop
int m[NFLOORS+1][MAX_RIDERS];   /* dynamic programming cost table */
// p[i][j] is the j-1th stop's floor, when i floor is jth stop's floor.
int p[NFLOORS+1][MAX_RIDERS];   /* dynamic programming parent table */

int floors_walked(int previous, int current){
    int nsteps=0;               /* total distance traveled */
    int i;                      /* counter */

    for(i=1; i<=nriders; i++)
        if((stops[i] > previous) && (stops[i] <= current))
            nsteps += min((stops[i]-previous), (current-stops[i]));
    
    return (nsteps);
}

int optimize_floors(){
    int i, j, k;                /* counters */
    int cost;                   /* costs placeholder */
    int laststop;               /* the elevator's last stop */

    /* if there is no stop, then the cost is sum of all destination */
    // m[i][0] means there is no stop, so every should walk from 0 floor.
    // p[i][0] means there is no -1 stop.
    for(i=0; i<=NFLOORS; i++){
        m[i][0] = floors_walked(0, MAXINT);
        p[i][0] = -1;
    }

    for(j=1; j<=nstops; j++)
        for(i=0; i<=NFLOORS; i++){
            m[i][j]=MAXINT;
            for(k=i; k>=0; k--){    // When k is from i floor to 0 floor, which floor is j-1th floor for minimun cost?
                cost = m[k][j-1] - floors_walked(k,MAXINT) + floors_walked(k,i) + floors_walked(i, MAXINT);
                if(cost < m[i][j]){
                    m[i][j] = cost;
                    p[i][j] = k;    // k is the j-1th stop's floor, when i floor is jth stop's floor.
                }
            }
        }

    laststop = 0;
    for(i=NFLOORS; i>=1; i--)
        if(m[i][nstops] < m[laststop][nstops])
            laststop = i;

    return (laststop);
}


void reconstruct_path(int lastfloor, int stops_to_go){
    if(stops_to_go > 1)
        reconstruct_path(p[lastfloor][stops_to_go], stops_to_go-1);
    stopped[count++]=lastfloor;
}

int print_floor(){
    int k;
    int temp;
    int gab;
    for(int i=1; i<=nriders; i++){
        k=abs((stopped[nstops]-stops[i]));
        temp=nstops;

        for(int j=nstops-1; j>=1; j--){
            if(k>abs((stopped[j]-stops[i]))){
                k=abs((stopped[j]-stops[i]));
                temp=j;
            }
        }

        printf("%d\n",stopped[temp]);

    }


}

int main(){
    
    scanf("%d %d",&nriders, &nstops);
    for(int i=1; i<=nriders; i++){
        scanf("%d",&stops[i]);
    }

    reconstruct_path(optimize_floors(),nstops);
    print_floor();
    return 0;
}
