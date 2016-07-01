#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <limits>
#include <iomanip>
#define LONG_MIN std::numeric_limits<long>::min()

namespace std {   }
using namespace std;

struct edge
{
   size_t u, v;
   long weight;
};

istream& operator>>(istream& is, edge& i)
{
   return is >> i.u >> i.v >> i.weight;
}

long bellman_ford(const vector<edge>& store, const size_t s, const size_t nodes, const long max_weight, bool& negative_cycle_detected)
{
   assert(s < nodes);

   negative_cycle_detected = false;

   vector<long> distance;
                distance.resize(nodes);

   for (size_t i = 0; i < distance.size(); distance[i] = max_weight, ++i);

   distance[s] = 0;

   long result_min = 0;

   for (size_t i = 0; i < (distance.size() - 1); ++i)
   {
      for (size_t j = 0; j < store.size(); ++j)
      {
         if ((distance[store[j].u] + store[j].weight) < distance[store[j].v])
         {
            distance[store[j].v] = distance[store[j].u] + store[j].weight;
            result_min = min(distance[store[j].v], result_min);
         }
      }
   }

   for (size_t i = 0; i < store.size(); ++i)
   {
      if ((distance[store[i].u] + store[i].weight) < distance[store[i].v])
      {
         negative_cycle_detected = true;
         break;
      }
   }

   return result_min;
}

int main(void)
{
   long max_weight = LONG_MIN;
   vector<edge> store;
   size_t nodes = 0, edges = 0;
   edge e = {0};
   
  int n, m;
  std::cin >> n >> m;
  nodes = n; edges = m; 

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    e.u = x-1;
    e.v = y -1;
    e.weight = w; 
    store.push_back(e);
    max_weight = max(max_weight, e.weight+1);
   
  }
  

   // cout << "Input size: " << store.size() << endl;
   assert(store.size() == edges);

   long min_weight = max_weight;
   bool abort = false;
   for (size_t i = 0; i < nodes; ++i)
   {
      bool negative_cycle_detected = false;
      long weight = bellman_ford(store, i, nodes, max_weight, negative_cycle_detected);

      if (negative_cycle_detected == false)
      {
         // cout << "Source: " << setw(4) << i << ", Weight: " << setw(4) << weight << endl;
         min_weight = min(min_weight, weight);
      }
      else
      {
         // cout << "Source: " << setw(4) << i << ", Negative Cycle Detected. No result. Aborting." << endl;
         abort = true;
         break;
      }
   }

   if (abort == false)
   {
      // cout << "Shortest shortest weight: " << setw(4) << min_weight << endl;
      cout << 0;
   }
   else
       cout << 1; 

   // cin.get();

   return 0;
}