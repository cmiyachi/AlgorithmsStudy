#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using std::vector;
using std::queue;


using std::cout;

queue<int> pathQueue;


int bipartite(vector<vector<int> > &adj,vector<int> dist, vector<int> prev, vector<int> color, vector<int> partition) {
  //write your code here
   while (pathQueue.empty() != true)
    {
        int u = pathQueue.front();
        // std:: cout << " u " << u << "\n"; 
        pathQueue.pop();
        for (int i = 0; i < adj[u].size(); i++)
        {
            // get adjacent vertex
            int vertex = adj[u][i];
            if (partition[u] == partition[vertex])
                return 0;
            else
            {
                if (color[vertex] == 0)
                {
                    color[vertex] = 1;
                    dist[vertex] = dist[u] + 1;
                    partition[vertex] = 3 - partition[u];
                    pathQueue.push(vertex);
                }
            }
        }
        color[u] = 2; 
    }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  
  vector<int> dist(n,INT_MAX);
  vector<int> prev(n,-1);
  vector<int> partition(n,0);
  vector<int> color(n,0); // 0 white 1 gray  2 black
  
  int s = 0; 
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  color[s] = 0; // s is gray - the start
  partition[s] = 1;
  dist[s] = 0;
  pathQueue.push(s);
  
  
  std::cout << bipartite(adj, dist, prev, color, partition);
}
