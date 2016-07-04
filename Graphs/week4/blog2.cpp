/*
procedure BellmanFord(list vertices, list edges, vertex source)
	// This implementation takes a vetext source
	// and fills distance array with shortest-path information

	// Step 1: initialize graph
	for each vertex v in vertices:
		if v is source 
			distance[v] := 0
		else 
			distance[v] := infinity

	// Step 2: relax edges repeatedly
	for i from 1 to size(vertices)-1:
		for each edge (u, v) with weight w in edges:
			if distance[u] + w < distance[v]:
				distance[v] := distance[u] + w

	// Step 3: check for negative-weight cycles
		for each edge (u, v) with weight w in edges:
			if distance[u] + w < distance[v]:
				error "Graph contains a negative-weight cycle"
*/

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

typedef struct {
    int u, v, w;
} Edge;
 

vector<Edge> edges;
vector<int> d; 
vector<int> neg_d;
vector<string> val;
/* d[i] is the minimum distance from source node s to node i */
 
#define INFINITY std::numeric_limits<int>::max()
 
void BellmanFord(int src) 
{
    int i, j;
 
    for (i = 0; i < d.size(); ++i) d[i] = 0/* INFINITY */;
    d[src] = 0;
 
    for (i = 0; i < d.size() - 1; ++i) {
        for (j = 0; j < edges.size(); ++j) {
            if (d[edges[j].u] + edges[j].w < d[edges[j].v]) {
                d[edges[j].v] = d[edges[j].u] + edges[j].w;
	    }
	}
    }
	
    // for (i = 0; i < d.size() - 1; ++i) {
        for (j = 0; j < edges.size(); ++j) {
            if (d[edges[j].u] + edges[j].w < d[edges[j].v]) {
               /*  printf("Graph contains a negative-weight cycle\n");
                cout << "from u to v " << edges[j].u << " " << edges[j].v << " \n"; */
                // neg_d[edges[j].u] = -1; 
                d[edges[j].v] = d[edges[j].u] + edges[j].w;
		// exit(1);
	    }
	// }
    }
    for (i = 0; i < neg_d.size(); ++i) neg_d[i] = INFINITY ;
    neg_d[src] = 0;
 
    for (i = 0; i < neg_d.size() - 1; ++i) {
        for (j = 0; j < edges.size(); ++j) {
            if (neg_d[edges[j].u] + edges[j].w < neg_d[edges[j].v]) {
                neg_d[edges[j].v] = neg_d[edges[j].u] + edges[j].w;
	    }
	}
    }
    
}
 
int main() 
{
    int i, j, w;
    int  k = 0;
    int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  edges.resize(m);
  d.resize(n);
  neg_d.resize(n);
  
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    edges[i].u = x-1;
    edges[i].v = y -1;
    edges[i].w = w; 
  }
  std::cin >> s;
  s--;
 
 

   /*  for (i = 0; i < n; ++i) printf("Node %d\t", i );
    printf("\n--------------------------------------\n"); */

    int source_vertex = s;
    BellmanFord(source_vertex);

    /* for (i = 0; i < n; ++i) printf("%d\t", d[i] );
    cout << "\n";
    for (i = 0; i < n; ++i) printf("%d\t", neg_d[i] );
    cout << "\n"; */
    for (i = 0; i < n; ++i)
    {
        if (i == s)
            cout << "0\n"; 
        else
        {
            if (d[i] < 0)
                cout << "-\n";
            else
            {
                if (neg_d[i] >= INFINITY)
                    cout << "*\n";
                else 
                    cout << neg_d[i] << "\n"; 
            }
        }
    }
 
   
    return 0;
}