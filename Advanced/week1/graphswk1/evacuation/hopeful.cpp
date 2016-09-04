#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void findAugPath(const vector<vector<int> >& G,
                 vector<vector<int> >& F,
                 vector<int>& pred) {
  const int N = G.size();

  // initialize predecessor path
  for (int i = 0; i < N; i++)
    pred[i] = -1;

  // need to mark vertices as they are visited
  vector<int> visited(N, false);

  // BFS uses a FIFO queue, push vertices
  queue<int> Q;

  // start with 0 (arbitrary source by convention)
  visited[0] = true;
  Q.push(0);

  // main loop
  while (!Q.empty()) {
    const int u = Q.front();
    Q.pop();

    // do not check for sink or mark visited here, better to do that
    // when pushing neighbors as the queue may have many vertices already

    for (int v = 0; v < N; v++)
      if (!visited[v])
        if ( (G[u][v] && (G[u][v] - F[u][v] > 0)) // forward arc
             || (G[v][u] && (F[v][u] > 0)) ) {    // backward arc
          visited[v] = true;
          pred[v] = u;
          Q.push(v);
          if (N-1 == v)
            return;
        }
  }
}

// returns the amount of flow augmentation
int applyAugPath(const vector<vector<int> >& G,
                 vector<vector<int> >& F,
                 const vector<int>& pred) {
  const int N = G.size();

  // find minimum flow along augmenting path
  int v = N-1, u, minFlow = INT_MAX;
  while (0 != v) {
    u = pred[v];

    if (G[u][v]) {
      // forward arc
      minFlow = min(minFlow, G[u][v] - F[u][v]);
    } else {
      // backward arc
      minFlow = min(minFlow, F[v][u]);
    }

    v = u;
  }

  // apply flow augmentation
  v = N-1;
  while (0 != v) {
    u = pred[v];

    if (G[u][v]) {
      // forward arc
      F[u][v] += minFlow;
    } else {
      // backward arc
      F[v][u] -= minFlow;
    }

    v = u;
  }

  return minFlow;
}

int main(int argc, char *argv[]) {
  // input number of vertices and edges
  cout << "input number of vertices and edges" << endl;
  int V, E;
  cin >> V >> E;

  // disallow anti-parallel edges so check for maximum V*(V-1)/2 edges
  if (E > V*(V-1)/2) {
    E = V*(V-1)/2;
    cout << "warning, maximum number of possible edges is " << E << endl;
  }

  // weighted graph, weights are capacities
  vector<vector<int> > G(V, vector<int>(V, 0));

  // construct random graph
  for (int i = 0; i < E; i++)
    while (true) {
      const int u = rand() % V,
                v = rand() % V;

      // no self loops
      if (u != v)
        // no anti-parallel arcs or overwriting of existing arcs
        if (0 == G[v][u] && 0 == G[u][v]) {
          G[u][v] = 1 + rand() % 100;
          break;
        }
    }

  // network flows
  vector<vector<int> > F(V, vector<int>(V, 0));

  // augmenting path is predecessor array
  vector<int> pred(V, 0);

  // augmenting path loop
  int totalFlow = 0;
  while (true) {
    findAugPath(G, F, pred);
    if (-1 == pred[V-1])
      break; // no path to sink node (taken to be N-1 for arbitrary convention)
    totalFlow += applyAugPath(G, F, pred);
  }

  cout << "total flow is " << totalFlow << endl;

  // print combined capacity and flow graph in GraphViz format
  cout << endl
       << "To generate a GraphViz graph from the following, do:" << endl
       << endl
       << "  dot -Tpng file_with_graph_G -o graph.png" << endl
       << endl
       << "-----file_with_graph_G begins here-----" << endl
       << "digraph G {" << endl
       << "  node [shape=circle]" << endl
       << "  {rank=source; 0;}" << endl
       << "  {rank=sink; " << (V-1) << ";}" << endl;
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      if (G[i][j]) {
        cout << "  " << i << " -> " << j
             << " [label=\"" << F[i][j] << "/" << G[i][j] << "\"";
        if (F[i][j])
          cout << ",color=red";
        cout << "];" << endl;
      }
  cout << "}" << endl;

  exit(0);
}