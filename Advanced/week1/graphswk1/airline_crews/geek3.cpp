// A C++ program to find maximal Bipartite matching.
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
 
// M is number of crews and N is number of planes
int  M = 0,N = 0;

// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool bpm(vector<vector<bool>> bpGraph, int u, bool seen[], vector<int> &matchR)
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
int maxBPM(vector<vector<bool>> bpGraph)
{
    // An array to keep track of the crews assigned to
    // planes. The value of matchR[i] is the crew number
    // assigned to plane i, the value -1 indicates nobody is
    // assigned.
    vector<int> matchR(N,-1);
   
    // Initially all planes are available
 
    
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
            cout << -1 << " "; 
        else
            cout << matchR[i]+1 << " "; 
    }
    cout << endl;
    return result;
}
vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right; // M is number of crews and N is number of planes
    N = num_left;
    M = num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    vector<vector<bool>> bpm_matrix(num_right, vector<bool>(num_left));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
     
    /*  for (int i = 0; i < num_left; ++i)
     {
      for (int j = 0; j < num_right; ++j) 
           cout << " " <<  adj_matrix[i][j] ;
        cout << endl;
     }
     cout << endl; */
    for (int i = 0; i < num_right; ++i)
     {
      for (int j = 0; j < num_left; ++j) 
      {
           // cout << " " <<  adj_matrix[j][i] ;
           bpm_matrix[i][j] = adj_matrix[j][i];
      }
        // cout << endl;
     } 
    
   /*  cout << " ***\n";
    for (int i = 0; i < num_right; ++i)
     {
      for (int j = 0; j < num_left; ++j) 
           cout << " " <<  bpm_matrix[i][j] ;
        cout << endl;
     }
     cout << endl; */
    return bpm_matrix;
  }
  
// Driver program to test above functions
int main()
{
    vector<vector<bool>> bpm_matrix = ReadData();
    
    // Let us create a bpGraph shown in the above example
   /*  bool bpGraph[M][N] = {  {1,1},
                        {1,0},
                        

                      };
 */
   /*  cout << "Maximum number of crews that can get plane is "
         <<  */maxBPM(bpm_matrix); 
 
    return 0;
}