#include<bits/stdc++.h>
#include<iostream>
#define NULL_VALUE -999999
#define NILL -999999
#define INFINITY 999999

using namespace std;

class Graph{
	int nVertices, nEdges ;
	bool directed ;
	int **gMat ; // store data in the graph
	int **prdMat;
	int **apMat;
	int *color,*parent,*dist,*discovered,*finished,time;
public:
	Graph(bool dir = false);
	void snVertices(int n);
	void addEdge(int u, int v,int w);
	void fldwrshll();
        void prntApSp();
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	gMat = 0 ;
	color = 0,parent = 0,dist = 0;
	discovered = 0,finished = 0,time = 0;
	directed = dir ;
}

void Graph::snVertices(int n)
{
    this->nVertices = n ;
    gMat = new int*[nVertices+3];
    prdMat     = new int*[nVertices+3];
    apMat     = new int*[nVertices+3];
    for(int i = 0;i < nVertices+3;i++)
    {
        gMat[i]= new int[nVertices+3];
        prdMat[i]= new int[nVertices+3];
        apMat[i]= new int[nVertices+3];
        for(int j = 0;j < nVertices+3;j++)
        {
            gMat[i][j] = (i==j)?0:INFINITY; //initial matrix is infinity
            prdMat[i][j] = NILL;
        }
    }
        color = new int[nVertices];
	parent = new int[nVertices] ;
	dist = new int[nVertices] ;
	discovered = new int[nVertices] ;
	finished = new int[nVertices] ;
}

void Graph::addEdge(int u, int v,int w)
{
    if(u < 0 || u > nVertices || v < 0 || v > nVertices) return;
    gMat[u][v] = w;
    if(!directed) gMat[v][u] = w;
    this->nEdges++ ;
}


void Graph::fldwrshll()
{
    int n = nVertices;

    for(int i = 1;i <= n;i++)
        {
        for(int j = 1;j <= n;j++)
           {
            apMat[i][j] = gMat[i][j];// default case
            if(i == j || gMat[i][j] == INFINITY)
            {
                prdMat[i][j] = NILL; //no predcsr
            }
            else if(i != j && gMat[i][j] < INFINITY)
            {
                prdMat[i][j] = i; //update prdcsr
            }
        }
    }

    for(int k = 1;k <= n;k++)
        {
        for(int i = 1;i <= n;i++)
           {
            for(int j = 1;j <= n;j++)
               {
                if((apMat[i][j] > apMat[i][k] + apMat[k][j]))
                  {
                    apMat[i][j] = apMat[i][k] + apMat[k][j];
                    prdMat[i][j] = prdMat[k][j];
                  }
            }
        }
    }
}

void Graph::prntApSp()
{
    printf("\nInitial graph:\n");
    for(int i = 1;i <= nVertices;i++)
    {
        for(int j = 1;j <= nVertices;j++)
           {
             if(gMat[i][j] == INFINITY)
             {
                printf("%4c ",236);
             }
             else
             {
                printf("%4d ",gMat[i][j]);
             }
           }
        printf("\n");
    }

    printf("\n\nAll pair shortest paths:\n");
    for(int i = 1;i<= nVertices;i++)
     {
        for(int j = 1;j <= nVertices;j++)
        {
            if(apMat[i][j] == INFINITY)
            {
                printf("%4c ",236);
            }
            else
            {
                printf("%4d ",apMat[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n\nPredecessor Matrics :\n");
    for(int i = 1;i <= nVertices;i++)
     {
        for(int j = 1;j <= nVertices;j++)
        {
            if(prdMat[i][j] == NILL)
            {
                printf("%4s ","NIL");
            }

            else
            {
                printf("%4d ",prdMat[i][j]);
            }
        }
        printf("\n");
     }
}


int main(void)
{
    freopen("inp.txt","r",stdin);
    int v,e;
    Graph g(true);
    scanf("%d%d", &v,&e);
    g.snVertices(v);

    for(int i = 0;i < e; i++)
    {
        int p,q,w;
        scanf("%d%d%d", &p,&q,&w);
        g.addEdge(p,q,w);
    }
    g.fldwrshll();
    g.prntApSp();
    return 0;
}
