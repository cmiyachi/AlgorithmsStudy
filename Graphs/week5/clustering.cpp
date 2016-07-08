#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <limits>
#include <utility>
#include <iostream>
#include <cmath>
#include <iomanip>

#define forsn(i, s, n) for(int i = s; i < n; ++i)
#define forn(i, n) forsn(i, 0, n)

using std::vector;
using std::pair;
using std::list;
using std::make_pair;
using std::cin;
using std::cout;
using std::endl;

typedef vector<int> vint;
typedef pair<double, pair<int, int>> edge;
typedef list<edge> edges;

vint rank;
vint parent;

void create_set(int x) {
  rank[x] = 0;
  parent[x] = x;
}

int find_set(int x) {
  if (x != parent[x]) parent[x] = find_set(parent[x]);
  return parent[x];
}

void merge_set(int x, int y) {
  if (rank[x] > rank[y]) parent[y] = x;
  else parent[x] = y;
  if (rank[x] == rank[y]) ++rank[y];
}

double kruskal(int n, edges& es, int no_clusters) {
  rank.resize(n);
  parent.resize(n);
  double cost = 0;
  int remaining = n-1;
  int counter = 0;
  int max = (n-1) - no_clusters;
  // cout << "max " << max << endl;
  
  double final_weight = 0.0; 
  
  forn(i, n) create_set(i);
  es.sort();
  
  for (auto& edge : es) {
    int u = find_set(edge.second.first);
    int v = find_set(edge.second.second);
    if (u == v) continue;
    merge_set(u, v);
    cost += edge.first;
    // cout << "edge weight  u v  c"<< edge.first << " " << u << " " << v << " " << counter << endl;
    
    if (counter > max)
    {
        final_weight = edge.first;
        return final_weight;
    }
    counter++;
    if (!--remaining) break;
  }

  if (remaining) return std::numeric_limits<double>::infinity();
  return final_weight;
}

int main() {

  size_t n;
  std::cin >> n;
  int no_edges = n*(n-1)/2;
  vector<int> x(n), y(n);
  double w;
 
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  int no_clusters;
  std::cin >> no_clusters;
  
  int index = 0;
  edges es;
  for (int i = 0; i < n; i++)
      for (int j = i+1; j < n; j++)
      {
          
          w = sqrt(((x[i]-x[j])*(x[i]-x[j])) + ((y[i]-y[j])*(y[i]-y[j])));
         // cout << " i j index w "  << i << " " << j << " " << index << " " << w << "\n";
          es.push_back(make_pair(w, make_pair(i,j)));
          index++;
      }

  

  // std::cout << "Cost of minimum spanning tree: " << kruskal(n, es) << std::endl;
  
  std::cout << std::setprecision(10) << kruskal(n, es, no_clusters) << std::endl;
  
 
}