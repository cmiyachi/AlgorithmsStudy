#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using std::vector;
using std::pair;
using std::priority_queue;
using std::cout;
using std::queue;


vector<int> dist;
vector<int> prev;
bool relax_occurred; 


// computes the distances for the nodes
void bellmanFord(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    int u = 0; //adj.size()-1;
    for (int j = 0; j < ((adj.size()-1)); j++) {
        u = j;
        for(unsigned i = 0; i < adj[j].size(); ++i) {
            
            int v = adj[j][i]; // vertext
            int w = cost[j][i];
            // cout << " j/u v w "  << u << " " << v <<   " " << w <<  " dist v dist u " << dist[v] << " " << dist[u] << "\n";
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;               
            }
        }
    }
}

void detect_negcycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
    int u = adj.size()-1;
    int j = u; 
    for(unsigned i = 0; i < adj[j].size(); ++i) {
        int v = adj[j][i]; // vertext
        int w = cost[j][i];
        // cout << " v w "  << v <<   " " << w <<  " dist v dist u " << dist[v] << " " << dist[u] << "\n";
        if(dist[v] > dist[u] + w) {
            relax_occurred = 1; 
        }
    }
}
// initalize
void initialize(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    
    dist.resize(adj.size());
    prev.resize(adj.size());
    
    for(size_t i = 0; i < dist.size(); ++i) {
        dist[i] = std::numeric_limits<int>::max();
        prev[i] = -1;
    }
    
    //dist[adj.size()-1] = 0;
    dist[0] = 0; 
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
 // cout << "s " << s << "\n";
  initialize(adj, cost);
  relax_occurred = false;
  bellmanFord(adj, cost);
  detect_negcycle(adj, cost);
    // cout << "relax " << ((relax_occurred == true)? 1: 0) << "\n"; 
    //int return_value = (relax_occurred == true)? 1: 0;
   /*  for (int i = 0; i < adj.size(); i++)
    {
     cout << "dist i " << i << " " << dist[i] << "\n";
    
    } */
    
    return ((relax_occurred == true)? 1: 0);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n/* +1 */, vector<int>());
  vector<vector<int> > cost(n/* +1 */, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
   
  }
  // add a vertext and connect it to every vertex with the distance of 0
  /* for (int j = 0; j < n; j++)
  {
      adj[n].push_back(j);
      cost[n].push_back(0);
  } */
  std::cout << negative_cycle(adj, cost);
  
  return 0;
}
