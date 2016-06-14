#include <iostream>
#include <vector>

using std::vector;
using std::pair;

using std::cout;

bool cycle_found = false; 
vector<int> order;


void explore(int v, vector<vector<int> > &adj, vector<bool> &visited)
{
    visited[v] = true;
   
    for (int i = 0; i < adj[v].size(); i++)
    {
        // get adjacent vertex
        int vertex = adj[v][i];
    
        if (visited[vertex] != true) // vertex not visited
        {
            explore(vertex, adj, visited);
            //visited[vertex] = false;
        }
        else
        {
            cycle_found = true;
            break;

        }
        
    }
    visited[v] = false;
    return; 
}
int acyclic(vector<vector<int> > &adj, vector<bool> &visited ) {
  //write your code here
  // for all items in the vector, mark as unvisited
  for (int i = 0; i < visited.size(); i++ )
  {
    
        explore(i, adj,visited);

   
  }
  int res = 0; 
  if (cycle_found == true) 
      res = 1;
  else
    res = 0; 
 
  return res; 
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<bool> visited(n, false); 
  vector<int> label(n,0);
  order.resize(n,0);

  
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  
  std::cout << acyclic(adj,visited);
}
