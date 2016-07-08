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

double kruskal(int n, edges& es) {
  rank.resize(n);
  parent.resize(n);
  double cost = 0;
  int remaining = n-1;
  forn(i, n) create_set(i);
  es.sort();
  for (auto& edge : es) {
    int u = find_set(edge.second.first);
    int v = find_set(edge.second.second);
    if (u == v) continue;
    merge_set(u, v);
    cost += edge.first;
    if (!--remaining) break;
  }

  if (remaining) return std::numeric_limits<double>::infinity();
  return cost;
}

int main() {

  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  double w;
 
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
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
  
  std::cout << std::setprecision(10) << kruskal(n, es) << std::endl;
}