#include <iostream>
#include <algorithm>
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

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = (order.size()-1); i > 0; --i) {
    std::cout << order[i] + 1 << " ";
  }
  std::cout << order[0] + 1 << " ";
}
