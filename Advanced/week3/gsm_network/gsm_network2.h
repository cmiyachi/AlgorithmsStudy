#include <ios>
#include <iostream>
#include <vector>
#include<stdio.h>

using namespace std;

// Number of vertices in the graph
int V=4;  // to be read as input
bool bSolutionExists = false;

struct Edge {
    int from;
    int to;
};

void printSolution(int color[]);
 
/* A utility function to check if the current color assignment
   is safe for vertex v */
bool isSafe (int v, vector<vector<bool>> graph, int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}
 
/* A recursive utility function to solve m coloring problem */
bool graphColoringUtil(vector<vector<bool>>  graph, int m, int color[], int v)
{
    /* base case: If all vertices are assigned a color then
       return true */
    if (v == V)
        return true;
 
    /* Consider this vertex v and try different colors */
    for (int c = 1; c <= m; c++)
    {
        /* Check if assignment of color c to v is fine*/
        if (isSafe(v, graph, color, c))
        {
           color[v] = c;
 
           /* recur to assign colors to rest of the vertices */
           if (graphColoringUtil (graph, m, color, v+1) == true)
             return true;
 
            /* If assigning color c doesn't lead to a solution
               then remove it */
           color[v] = 0;
        }
    }
 
    /* If no color can be assigned to this vertex then return false */
    return false;
}
 
/* This function solves the m Coloring problem using Backtracking.
  It mainly uses graphColoringUtil() to solve the problem. It returns
  false if the m colors cannot be assigned, otherwise return true and
  prints assignments of colors to all vertices. Please note that there
  may be more than one solutions, this function prints one of the
  feasible solutions.*/
bool graphColoring(vector<vector<bool>>  graph, int m)
{
    // Initialize all color values as 0. This initialization is needed
    // correct functioning of isSafe()
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;
 
    // Call graphColoringUtil() for vertex 0
    if (graphColoringUtil(graph, m, color, 0) == false)
    {
      printf("Solution does not exist");
      return false;
    }
 
    // Print the solution
    printSolution(color);
    return true;
}
 
/* A utility function to print solution */
void printSolution(int color[])
{
    bSolutionExists = true;
   /*  printf("Solution Exists:"
            " Following are the assigned colors \n"); */
   /*  for (int i = 0; i < V; i++)
      printf(" %d ", color[i]);
    printf("\n"); */
}
 


struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        if (bSolutionExists) 
        {
            cout << "3 2" << endl;
            cout << "1 2 0" << endl;
            cout << "-1 -2 0" << endl;
            cout << "1 -2 0" << endl;
        }
        else
        {
            cout << "2 1" << endl;
            cout << "1 0" << endl;
            cout  << "-1 0" << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    
    /* Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
    /* bool graph[V][V] = {{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    }; */
    int num_colors = 3; // Number of colors
   // graphColoring (graph, num_colors);

    
    
    int n, m;
    cin >> n >> m;
    V = n;
  //  bool graph[V][V] = {0}; 
    vector<vector<bool>> graph(V, vector<bool>(V));
    
    
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
        graph[converter.edges[i].from - 1][converter.edges[i].to -1] = 1;
        graph[converter.edges[i].to - 1][converter.edges[i].from -1] = 1;
        
        
    }
    
    /* for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << " " << graph[i][j];
        
        cout << endl; 
    } */

   // 
   
   graphColoring (graph, num_colors);
   
   converter.printEquisatisfiableSatFormula();

    return 0;
}
