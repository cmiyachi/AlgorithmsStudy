// A C++ program to find maximal Bipartite matching.
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
 
// M is number of crews and N is number of planes
#define M 2
#define N 2
 
// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool bpm(bool bpGraph[M][N], int u, bool seen[], vector<int> &matchR)
{
    // Try every plane one by one
    for (int v = 0; v < N; v++)
    {
        // If crew u is interested in plane v and v is
        // not visited
        if (bpGraph[u][v] && !seen[v])
        {
            seen[v] = true; // Mark v as visited
 
            // If plane 'v' is not assigned to an crew OR
            // previously assigned crew for plane v (which is matchR[v]) 
            // has an alternate plane available. 
            // Since v is marked as visited in the above line, matchR[v] 
            // in the following recursive call will not get plane 'v' again
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
 
// Returns maximum number of matching from M to N
int maxBPM(bool bpGraph[M][N])
{
    // An array to keep track of the crews assigned to
    // planes. The value of matchR[i] is the crew number
    // assigned to plane i, the value -1 indicates nobody is
    // assigned.
    vector<int> matchR(N,-1);
   
    // Initially all planes are available
    
  for (int i = 0; i < N; i++)
        cout << " " << matchR[i];
    cout << endl;
    
    int result = 0; // Count of planes assigned to crews
    for (int u = 0; u < M; u++)
    {
        // Mark all planes as not seen for next crew.
        bool seen[N];
        memset(seen, 0, sizeof(seen));
 
        // Find if the crew 'u' can get a plane
        if (bpm(bpGraph, u, seen, matchR))
            result++;
    }
    
    for (int i = 0; i < N; i++)
    {
        if (matchR[i] == -1)
            cout << " " << -1; 
        else
            cout << " " << matchR[i]+1; 
    }
    cout << endl;
    return result;
}
 
// Driver program to test above functions
int main()
{
    // Let us create a bpGraph shown in the above example
    bool bpGraph[M][N] = {  {1,1},
                        {1,0},
                        

                      };
 
    cout << "Maximum number of crews that can get plane is "
         << maxBPM(bpGraph);
 
    return 0;
}