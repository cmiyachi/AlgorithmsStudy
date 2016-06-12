#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;

void explore(int cc, int v, vector<vector<int> > &adj, vector<bool> &visited, vector<int> &label)
{
   // cout << " v " << v << " cc " << cc << "\n";
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

int reach(vector<vector<int> > &adj, int x, int y, vector<bool> visited, vector<int> label) {
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
   
  // cout << " x " << label[x] << " y " << label[y] << "\n"; 
  return (label[x] == label[y] ? 1 : 0);
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
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1, visited, label);
}
