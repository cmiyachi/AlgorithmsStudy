// A Dynamic Programming based solution for 0-1 Knapsack problem
#include<stdio.h>
#include <vector>
#include <iostream>
using std::cin;
using std::cout;
using std::max; 
using std::endl; 

using std::vector;
 
// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, vector<int> &wt, vector<int> val, int n)
{
   int i, w;
   //int K[n+1][W+1];
   vector<vector<int> > K(n+1, vector<int>(W+1));

 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
 
   return K[n][W];
}
int main() {
  int n, W;
  std::cin >> W >> n;  // C is W and N  is n
  vector<int> w(n);
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
	v[i] = w[i];
  }
  
  int* vv = &v[0];
  int* ww = &w[0];
  // std::cout << optimal_weight(W, w) << '\n';
 //  cout<<knapsack(vv,ww,W,n)<<endl;
  cout<<knapSack(W, w, v, n)<<endl;
}
/* int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d", knapSack(W, wt, val, n));
    return 0;
} */