#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
    
   used[x] = true;
   
    for (int i = 0; i < adj[x].size(); i++)
    {
        
        // get adjacent vertex
        int vertex = adj[x][i];
   // cout << " x  vertex "  << x << " " << vertex << "\n";
        if (used[vertex] != true) // vertex not visited
        {
            dfs(adj, used, order, vertex);
        }
        
            
    }
   // used[x] = false;
    order.push_back(x);
    return; 
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  int x = 0; 
  for (int i = 0; i < adj.size(); i++ )
  {
      if (used[i] != true)
        dfs(adj, used, order, i);
   // cout << " *************\n";
  }
  
  return order;
}
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

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > rev_adj, vector<bool> visited, vector<int> label) {
    int res = 0;
   
    // first find the topo order of the vertices
    vector<int> used(adj.size(), 0);
    vector<int> order;
    //write your code here
    int x = 0; 
    for (int i = 0; i < adj.size(); i++ )
    {
      if (used[i] != true)
        dfs(adj, used, order, i);
    // cout << " *************\n";
    }
    // print out order to check
/*     for (size_t i = (order.size()-1); i > 0; --i) {
        std::cout << order[i] + 1 << " ";
      }
      std::cout << order[0] + 1 << " \n"; */
      
  // now in the order found, search through for strong connections
  // for all items in the vector, mark as unvisited
  int cc = 1;
  // for (int i = 0; i < visited.size(); i++ )
  while (order.empty() != true)
  {
    int v_rev = order.back();
    order.pop_back();
    if (visited[v_rev] != true)
    {
        explore(cc, v_rev, rev_adj,visited, label);
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
  vector<vector<int> > rev_adj(n, vector<int>());
  vector<bool> visited(n, false); 
  vector<int> label(n,0);
  
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    rev_adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, rev_adj, visited, label);
}
