#include<iostream>
#define inf 100000000
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<string>


using namespace std;

class graph
{
	int nVertics;
	int **R;
	int **Cap;
	int *par;
	bool *vs;

public:
	graph(int nVertics)
	{
		this->nVertics = nVertics;
        R = new int*[nVertics + 1];
		for (int i = 0; i <= nVertics; i++)
        {
            R[i] = new int[nVertics + 1];
        }
        Cap = new int*[nVertics + 1];
		for (int i = 0; i <= nVertics; i++)
        {
            Cap[i] = new int[nVertics + 1];
        }

		for (int i = 0; i <= nVertics; i++)
		{
			for (int j = 0; j <= nVertics; j++)
            Cap[i][j] = 0;
		}

		vs = new bool[nVertics + 1];//vist or not
		par = new int[nVertics + 1];
	}

	void addEdge(int u, int v, int w)
	{
	    if(u<=0 || v<=0 || u>nVertics || v>nVertics) return;
		Cap[u][v] = w;
	}

	bool bfs(int s, int t)
	{
		for (int i = 0; i <= nVertics; i++)
        {
            vs[i] = 0;
        }

		queue<int> a;

		vs[s] = 1;
		a.push(s);
		par[s] = -1;

		while (!a.empty())
		{
			int u = a.front();
			a.pop();

			for (int v = 1; v <= nVertics; v++)
			{
				if (!vs[v] && R[u][v] > 0)
				{
					par[v] = u;
					vs[v] = 1;
					a.push(v);
				}
			}
		}

		return vs[t] == 1;
	}


	/*int fordFulkerson(int s, int t)
	{
		//initially Ridual Cap is equal to the actual Cap
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
				R[i][j] = Cap[i][j];
		}

		int flow = 0;
		int minFlow;
		int u, v;

		//augmenting the path to s to t while it is possible
		while (bfs(s, t))
		{
			minFlow = inf;

			//determine the minimum Ridual Cap in the path

            v=t;
			for (v=t; v!=s; v=par[v])
            {
               u = par[v];
               minFlow = min(minFlow, R[u][v]);

               v = u;
				if (v == s)
					break;
            }



			//update Ridual Cap

            v=t;
			for (v=t; v != s; v=par[v])
            {
            u = par[v];
            R[u][v] -= minFlow;
            R[v][u] += minFlow;
            v = u;

				if (v == s)
					break;

            }


			flow = minFlow;
		}

		return flow;
	}*/

    int fordFulkerson(int s, int t)
	{

		for (int i = 0; i <= nVertics; i++)
		{
			for (int j = 0; j <= nVertics; j++)
            {
                R[i][j] = Cap[i][j];
            }
		}

		int fl = 0;
		int mnFlw;
		int u, v;

		//augmenting  path to s to t if it is possible
		while (bfs(s, t))
		{
			mnFlw = inf;
            v = t;
			while (1)
			{
				u = par[v];
				mnFlw = min(mnFlw, R[u][v]);
				v = u;
				if (v == s)
                {
                    break;
                }
			}
            v = t;
			while (1)
			{
				u = par[v];
				R[u][v] -= mnFlw;
				R[v][u] += mnFlw;
				v = u;

				if (v == s)
                {
                    break;
                }
			}
          fl =fl + mnFlw;
		}


		return fl;
	}

	void flowThroughEdge()
	{

		for (int i = 1; i <= nVertics; i++)
		{
			for (int j = 1; j <= nVertics; j++)
			{
				if (Cap[i][j] > 0)
				{
					printf(" %d ---- %d = %d\n", i, j, Cap[i][j] - R[i][j]);
				}
			}
		}
	}

	void DFS(int s)
	{
		vs[s] = 1;
		for (int i = 1; i <= nVertics; i++)
		{
			if (R[s][i] && !vs[i])
            {
                DFS(i);
            }
		}
	}

	void mnCut(int s)
	{
		for (int i = 0; i <= nVertics; i++)
        {
            vs[i] = 0;
        }

		DFS(s);
        printf("Min cut edges are: \n");
		for (int i = 1; i <= nVertics; i++)
		{
			for (int j = 1; j <= nVertics; j++)
			{
				if (vs[i] && !vs[j] && Cap[i][j])
                {
                    printf("%d -- %d\n", i, j);
                }
			}
		}
	}
};

int main()
{
	freopen("in.txt", "r", stdin);

	int i,j,k,vr,e,s,t,u,v,w;

	scanf("%d%d", &vr, &e);

	graph g(vr);

	for (i = 0; i < e; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		g.addEdge(u, v, w);
	}

	scanf("%d%d", &s, &t);

	printf("Max Flow is\n ");
	cout << g.fordFulkerson(s, t) << endl;
	g.flowThroughEdge();
	g.mnCut(s);

	return 0;
}
