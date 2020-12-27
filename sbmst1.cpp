#include<bits/stdc++.h>
#define NULL_VALUE -99999
#define infin 99999999.99
#define MAX_HEAP_SIZE 100000
#define highest 1000
#define MAXREAL 999999.0
#define falsevalue -1
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;

FILE *f;
class ArrayList
{
  public:
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
	int weightLst[highest][highest];
    ArrayList() ;
	~ArrayList() ;
	int srchem(int item) ;
    void insertItem(int olditem,int newitem,int weight) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;

ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
	for (int i=0; i<highest;i++)
    {
        for(int j=0;j<highest;j++)
        {
            weightLst[i][j]=0;
        }
    }
}

void ArrayList::insertItem(int olditem,int newitem, int weight)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	weightLst[olditem][newitem]=weight;
	length++;
}

int ArrayList::srchem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = srchem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
       printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
    for (int i=0; i<highest;i++)
    {
        for(int j=0;j<highest;j++)
        {
            weightLst[i][j]=0;
        }
    }
}
class HeapItem
{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
		A[0].key=MAXREAL;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}
	void printl()
	{
	    for(int i=1;i<=heapLength;i++)
        {
            printf("%d",A[i].data);
        }
        printf("\n");
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {

        A[++heapLength].data=data;
        A[heapLength].key=key;
        map[A[heapLength].data]=heapLength;
        buHeapify(heapLength);
     }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin()
	{
     if(Empty())
     {
         printf("empty heap....\n");
         return A[0];
     }
     if(heapLength==1)
     {
         heapLength=0;
         map[A[1].data]=0;
         A[1].key=MAXREAL;
         return A[1];

     }
       HeapItem ret = A[1];
       map[A[heapLength].data] = map[A[1].data];
       A[1]=A[heapLength--];
       heapify(1);
       return ret ;
     }


    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key)
	{

        if(map[data]>heapLength || map[data]<=0)
        {
            printf("Element does not exist ....\n");
            return;
        }
        A[map[data]].key=key;
        buHeapify(map[data]);



	}


    //This function returns the key value of a data stored in heap
	float getKey(int data)
	{
		int i = map[data];
		return A[i].key;
		printf("i am printing\n");
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void swap_node(int i , int j)
    {
        HeapItem t;
        t=A[i];
        A[i]=A[j];
        map[A[i].data]=i;
        A[j]=t;
        map[A[j].data]=j;
    }
	void heapify(int i)
	{
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly

				swap_node(i,smallest);
				i=smallest;

			}

		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i)
	{

      heapify(i);
      while(i>1 && A[i].key < A[i/2].key)
      {
          swap_node(i,i/2);
          i=i/2;
      }
	}
	bool srch(int d)
      {
        for(int i=1;i<=heapLength;i++)
        {
          if(A[i].data=d)
          {
              return true;
          }
          return false;
        }
      }


    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    void clr1()
    {
      if(map) delete[] map;
      if(A) delete [] A;
      map=0;
      A=0;

    }
	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};


//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
  public :
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;


  public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
    void printGraph();
	int getWeight(int u, int v);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;


}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

}

int Graph::getWeight(int u, int v)
{
    return adjList[u].weightLst[u][v];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(u,v,w) ;
	adjList[u].insertItem(v,u,w) ;

}

void Graph::dfs()
{
   for( int i=0;i<nVertices;i++)
    {
        color[i]=WHITE;
        parent[i]=-1;
        st[i]=INFINITY;
        et[i]=INFINITY;

    }
    t=0;
    for(int i=0;i<nVertices;i++)
    {
        if(color[i]==WHITE)
        {
            dfsvst(i);
        }
    }

}
void Graph::dfsvst(int a)
{
    t=t+1;
    color[a]=GREY;
    st[a]=t;
    int k=0;
    while(k<adjList[a].getLength())
    {

        int b=adjList[a].getItem(k);
        if(color[b]==WHITE)
        {
            parent[b]=a;
            dfsvst(b);
        }
        k++;
    }
    t=t+1;
    et[a]=t;
    color[a]=BLACK;

}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        return NULL_VALUE;
    }
    bfs(u);

    return dst[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
  if(adjList)
  {
      delete[]adjList;
      adjList=0;
  }
  if(color)
  {
      delete[]color;
      color=0;
  }
  if(dst)
  {
      delete[]dst;
      dst=0;
  }
  if(parent)
  {
      delete[]parent;
      parent=0;
  }
  if(st)
  {
      delete[]st;
      st=0;
  }
  if(et)
  {
      delete[]et;
      et=0;
  }

}




void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}


Graph::~Graph()
{
  if(adjList)
  {
      delete[]adjList;
      adjList=0;
  }


}
