#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using std::vector;
using std::cout;
using std::queue;
using std::pair;
using std::priority_queue;


typedef std::pair<int, float> graphPair;
typedef std::vector<std::vector<graphPair> > dijkstraGraph;

dijkstraGraph graph;
vector<float> dist;
vector<int> prev;
vector<int> path;

// comperator
struct Comperator {
    int operator() (const graphPair & pair1, const graphPair & pair2) {
        return pair1.second > pair2.second;
    }
};

std::priority_queue<graphPair, std::vector<graphPair>, Comperator> priorityQueue;

// searches the best path
bool createPath(const int & s, const int & t) {
    
    bool hasPath = true;
    
    int p = t;
    
    path.push_back(t);
    
    while(p != s) {
        p = prev[p];
        
        if(p == -1) {
            hasPath = false;
            break;
        }
        
        path.push_back(p);
    }
    
    return hasPath;
}

// prints the path to the console
void printPath(const int & t) {
    
    std::cout << dist[t] << std::endl;
    
    for(int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}



// computes the distances for the nodes
void computeDistances(const int & t) {
    
    while(!priorityQueue.empty()) {
        int u = priorityQueue.top().first;
        
        if(u == t) {
            break;
        }
        
        priorityQueue.pop();
        
        for(unsigned i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i].first;
            float w = graph[u][i].second;
            
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                
                priorityQueue.push(std::make_pair(v, dist[v]));
            }
        }
    }
}
// initalize
void initialize(vector<vector<int> > &adj, vector<vector<int> > &cost, int s) {
    
    dist.resize(adj.size());
    prev.resize(adj.size());
    graph.resize(adj.size());
    
   // cout << graph.size() << "\n";
    // build the graph
    for( size_t j=0; j < graph.size(); j++)
    {
      //  cout << adj[j].size() << "\n";
        for (size_t k=0; k < adj[j].size(); k++)
        {
        //    cout << " j k adj cost " << j << " " << k << " " << adj[j][k] << " " << cost[j][k] << "\n";
            graph[j].push_back(std::make_pair(adj[j][k], cost[j][k]));
        }
    }
    
    
    for(size_t i = 0; i < dist.size(); ++i) {
        dist[i] = std::numeric_limits<int>::max();
        prev[i] = -1;
    }
    
    dist[s] = 0;
    
    priorityQueue.push(std::make_pair(s, dist[s]));
}
int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code here
  initialize(adj, cost, s);
  computeDistances(t);

   if(createPath(s, t)) 
   {
      //  printPath(t);
        return dist[t]; 
   }
    else
        return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
