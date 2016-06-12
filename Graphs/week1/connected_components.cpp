#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;

void explore(int cc, int v, vector<vector<int> > &adj, vector<bool> &visited, vector<int> label)
{
    visited[v] = true;
    label[v] = cc; 
    for (int i = 0; i < adj[v].size(); i++)
    {
        // get adjacent vertex
        int vertex = adj[v][i];
        if (visited[vertex] != true) // vertex not visited
        {
            explore(cc, vertex, adj, visited, label);
        }
    }
    return; 
}
int number_of_components(vector<vector<int> > &adj,vector<bool> visited, vector<int> label) {
  int res = 0;
  //write your code here
  // for all items in the vector, mark as unvisited
  int cc = 1;
  for (int i = 0; i < visited.size(); i++ )
  {
    if (visited[i] != true)
    {
        explore(cc, i, adj,visited, label);
        cc++;
    }
  }
  res = cc -1; 
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<bool> visited(n, false); 
  vector<int> label(n,0);
  
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
    // cout << " x " << x << " y "<< y << " " << adj[x-1][0] << " " << adj[y-1][0] << "\n";

  }
  std::cout << number_of_components(adj, visited, label);
}
