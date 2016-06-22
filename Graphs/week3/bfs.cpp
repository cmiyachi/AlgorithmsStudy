#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::cout;

queue<int> pathQueue;
void bfs(vector<vector<int> > &adj, int s, int t, vector<int> dist, vector<int> prev)
{
    while (pathQueue.empty() != true)
    {
        int u = pathQueue.front();
        std:: cout << " u " << u << "\n"; 
        pathQueue.pop();
        for (int i = 0; i < adj[u].size(); i++)
        {
            // get adjacent vertex
            int vertex = adj[u][i];
            std::cout << " vertex u i " << vertex << " " << u << " " << i << "\n";
            if (dist[vertex] == 10000)
            {
                pathQueue.push(vertex);
                dist[vertex] = dist[u] + 1; 
                prev[vertex] = u; 
            }
        }
    }
}
int distance(vector<vector<int> > &adj, int s, int t, vector<int> dist, vector<int> prev) {
  //write your code here
  bfs(adj, s, t, dist, prev);
  vector<int> result;
  int u = t;
  while (u != s)
  {
      cout << " u inside " << u << "\n"; 
      result.push_back(u);
      u = prev[u]; 
      cout << " prev "  << u << "\n"; 
  }
  return result.size();
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<int> dist(n,10000);
  vector<int> prev(n,-1);
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
    std:: cout << x << " " << y << "\n"; 
  }
  int s, t;

  std::cin >> s >> t;
  s--, t--;
  dist[s] = 0; 
  pathQueue.push(s);
  std:: cout << "q size " << pathQueue.size() << "\n"; 
  std::cout << distance(adj, s, t, dist, prev);
}
