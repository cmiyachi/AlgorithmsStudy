#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::cout;
using std::endl;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest, vector<vector<int> > &ww) {
 
  int N = distance.size();
  vector<int> pre(N,-1);
  distance[s] = 0;
  
  // bellman-Ford
  for (int k = 0; k < N; ++k )
      for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
              if (distance[i] + ww[i][j] < distance[j])
              {
                  distance[j] = distance[j] + ww[i][j];
                  pre[j] = i;
              }
   
   // negative cycles
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
          if (distance[i] + ww[i][j] < distance[j])
          {
              cout << "Node j is part of negative cycle "<< j << endl;
          }
          
   for (int k = 0; k < N; ++k )
   {
       cout << "pre  k " << pre[k] << " " << k << endl;
   }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  vector<vector<int> > ww(n,vector<int>(m));
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    ww[x-1][y-1] = -log(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest, ww);
  /* for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  } */
}
