#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

#define INT_MIN std::numeric_limits<int>::min()
#define MAX_INT_BF std::numeric_limits<int>::max()

using namespace std;

// I find it way easier to think of these algorithms in edges
//  each edge has a weight
struct edge
{
   size_t u, v;
   int weight;
};

vector<int> bf_distance;
vector<int> distance_to_s; 
 
int bellman_ford(const vector<edge>& store, const size_t s, const size_t nodes, const int max_weight, bool& negative_cycle_detected)
{
   assert(s < nodes);

   negative_cycle_detected = false;

  
   bf_distance.resize(nodes);

   // set the bf_distances to infinity
   for (size_t i = 0; i < bf_distance.size()-1; bf_distance[i] = 0 /* MAX_INT_BF */  , ++i);

   // set the bf_distance for the start node to 0
   bf_distance[s] = 0;

   // initilize the minimum bf_distance to 0
   int result_min = 0;

   // run through the algorithm for all the vertices/nodes -1  - 
   for (size_t i = 0; i < (bf_distance.size() - 1); ++i)
   {
      for (size_t j = 0; j < store.size(); ++j)
      {
          cout << " BEFORE j v u w dist " << j << "  " << store[j].v << " " << store[j].u << " " << store[j].weight << " " << bf_distance[store[j].v] << " " << bf_distance[store[j].u] << "\n"; 
          // relax the edges
         if ((bf_distance[store[j].u] + store[j].weight) < bf_distance[store[j].v])
         {
            bf_distance[store[j].v] = bf_distance[store[j].u] + store[j].weight;
            cout << " j v u w dist " << j << "  " << store[j].v << " " << store[j].u << " " << store[j].weight << " " << bf_distance[store[j].v] << " " << bf_distance[store[j].u]<< "\n"; 
            // store the minimum bf_distance
            result_min = min(bf_distance[store[j].v], result_min);
         }
      }
      // distance after loop
      cout << "*** i " << i << "\n";
       for (int k = 0; k < bf_distance.size()-1; k++)
       {
            cout << "k dist "  << k << " " << bf_distance[k] << "\n";
       
        }
   }

   // detect a negative cycle by going through one more time - all the edges
   // if a relaxation can occur we have a negative cycle
   for (size_t i = 0; i < store.size(); ++i)
   {
       cout << " FINAL i v u w dist " << i << "  " << store[i].v << " " << store[i].u << " " << store[i].weight << " " << bf_distance[store[i].v] << " " << bf_distance[store[i].u] << "\n"; 
      if ((bf_distance[store[i].u] + store[i].weight) < bf_distance[store[i].v])
      {
          bf_distance[store[i].v] = bf_distance[store[i].u] + store[i].weight;
         negative_cycle_detected = true;
         cout << " i v u w dist " << i << "  " << store[i].v << " " << store[i].u << " " << store[i].weight << " " << bf_distance[store[i].v] << " " << bf_distance[store[i].u]<< "\n"; 
         distance_to_s[store[i].v] = -1; 
      }
   }

   return result_min;
}

int main(void)
{
   int max_weight = INT_MIN;
   // make a vector of all the edges
   vector<edge> store;
   // initialize the number of vertices/nodes and the number of edges
   size_t nodes = 0, edges = 0;
   // initalize the first edge structure for use
   edge e = {0};
   
   // read in the data from the user and set the variables
  int n, m, s;
  std::cin >> n >> m;
  nodes = n; edges = m; 
  distance_to_s.resize(nodes);

  // for the all edges read in the start end and weight
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    e.u = x-1;
    e.v = y -1;
    e.weight = w; 
    store.push_back(e);
    // keep track of the maximum weight
    max_weight = max(max_weight, e.weight+1);
   
  }
   std::cin >> s;
  s--;

   // cout << "Input size: " << store.size() << endl;
   // make sure the size of the vector is the size given by the user
   assert(store.size() == edges);

   // set the min weight to the max weight
   int min_weight = max_weight;
   bool abort = false;
   
   // for all the vertices - call bellman ford with that vertex/node as the start
  /*  for (size_t i = 0; i < nodes; ++i)
   { */
      bool negative_cycle_detected = false;
      int weight = bellman_ford(store, s, nodes, max_weight, negative_cycle_detected);

      // if no negative cycle was detected, continue on, otherwise stop!
      if (negative_cycle_detected == false)
      {
         // cout << "Source: " << setw(4) << s << ", Weight: " << setw(4) << weight << endl;
         min_weight = min(min_weight, weight);
      }
      else
      {
         // cout << "Source: " << setw(4) << s << ", Negative Cycle Detected. No result. Aborting." << endl;
         abort = true;
         // break;
      }
   // }

   if (abort == false)
   {
      /* cout << "Shortest shortest weight: " << setw(4) << min_weight << endl; */
      cout << 0;
   }
   else
       cout << 1; 

   for (int i = 0; i < bf_distance.size(); i++)
   {
       cout << "i dist "  << i << " " << bf_distance[i] << "\n";
       cout << "i dist s "  << i << " " << distance_to_s[i] << "\n";
   }
   


   return 0;
}