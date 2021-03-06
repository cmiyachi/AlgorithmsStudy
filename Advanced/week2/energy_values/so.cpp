/* Program to demonstrate gaussian <strong class="highlight">elimination</strong>
   on a set of linear simultaneous equations
 */

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double eps = 1.e-15;

/*Preliminary pivoting strategy
  Pivoting function
 */
double pivot(vector<vector<double> > &a, vector<double> &b, int i)
 {
     int n = a.size();
     int j=i;
     double t=0;

     for(int k=i; k<n; k+=1)
     {
         double aki = fabs(a[k][i]);
         if(aki>t)
         {
             t=aki;
             j=k;
         }
     }
     if(j>i)
     {
         double dummy;
         for(int L=0; L<n; L+=1)
         {
             dummy = a[i][L];
             a[i][L]= a[j][L];
             a[j][L]= dummy;
         }
         double temp = b[j];
         b[i]=b[j];
         b[j]=temp;
     }
     return a[i][i];
 }        



/* Forward <strong class="highlight">elimination</strong> */
void triang(vector<vector<double> > &a, vector<double> &b) 
{
    int n = a.size();
    for(int i=0; i<n-1; i+=1)
    {
        double diag = pivot(a,b,i);
        if(fabs(diag)<eps)
        {
            cout<<"zero det"<<endl;
            return;
        }
        for(int j=i+1; j<n; j+=1)
        {
            double mult = a[j][i]/diag;
            for(int k = i+1; k<n; k+=1)
            {
                a[j][k]-=mult*a[i][k];
            }
            b[j]-=mult*b[i];
        }
    }
}

/*
DOT PRODUCT OF TWO VECTORS
*/
double dotProd(vector<double> &u, vector<double> &v, int k1,int k2)
{
  double sum = 0;
  for(int i = k1; i <= k2; i += 1)
  {
     sum += u[i] * v[i];
  }
  return sum;
}

/*
BACK SUBSTITUTION STEP
*/
void backSubst(vector<vector<double> > &a, vector<double> &b, vector<double> &x)
{
    int n = a.size();
  for(int i =  n-1; i >= 0; i -= 1)
  {
    x[i] = (b[i] - dotProd(a[i], x, i + 1,  n-1))/ a[i][i];
  }
}
/*
REFINED GAUSSIAN <strong class="highlight">ELIMINATION</strong> PROCEDURE
*/
void gauss(vector<vector<double> > &a, vector<double> &b, vector<double> &x)
{
   triang(a, b);
   backSubst(a, b, x);
}                               

// EXAMPLE MAIN PROGRAM
int main()
{
    int n;
    cin >> n;
    vector<vector<double> > a;
    vector<double> x;
    vector<double> b;
    for (int i = 0; i < n; i++) {
        vector<double> temp;
        for (int j = 0; j < n; j++) {
            int no;
            cin >> no;
            temp.push_back(no);
        }
        a.push_back(temp);
        b.push_back(0);
        x.push_back(0);
    }
    /* 
    for (int i = 0; i < n; i++) {
        int no;
        cin >> no;
        b.push_back(no);
        x.push_back(0);
    }
    */

  gauss(a, b, x);
  for (size_t i = 0; i < x.size(); i++) {
      cout << x[i] << endl;
  }
   return 0;
}