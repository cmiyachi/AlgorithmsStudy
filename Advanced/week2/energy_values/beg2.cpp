#include <iostream>
#include <cmath>
#include <stdio.h>
#include <iomanip>

const double EPS = 1e-6;
const int PRECISION = 20;
using namespace std;

int main()
{
    int n;//n is the number of unknowns
    // cout<<"n: ";
    cin>>n;
    double ** A;//Declare a pointer to pointer to use as a dynamic 2D array
    A=new double*[n];
    for (int i=0;i<n;i++)
    {
        A[i]=new double[n+1];
    }
    // cout<<'\n';
    for (int r=0;r<n;r++)//Get the array elements from the user
    {
        for (int c=0;c<n+1;c++)
        {
            // cout<<"A["<<r+1<<"]"<<"["<<c+1<<"] :";
            cin>>A[r][c];
        }
    }
    // cout<<'\n';
    /* for (int r=0;r<n;r++)//Display the array on the console screen
    {
        for (int c=0;c<n+1;c++)
        {
            cout<<" "<<A[r][c]<<" ";
        }
        cout<<'\n';
    } */

    for (int a=0;a<n;a++)
    {
        double k=A[a][a];
        for(int x=0;x<n+1;x++)
        {
            A[a][x]=A[a][x]/k;
        }
        for (int i=0;i<n;i++)
        {
            double m=A[i][a];
            for (int j=0;j<n+1;j++)
            {
                if(i==a)continue;
                A[i][j]=A[i][j]-A[a][j]*m;
            }
        }
    }
    // cout<<"Solution of the system:"<<'\n'<<'\n';
    std::cout.precision(20);
    for (int r=0;r<n;r++)//The result after apllying the gauss algorithm
    {
       /*  for (int c=0;c<n+1;c++)
        { */
            cout<<  A[r][n]<<std::endl;
            // printf("%g ",A[r][n] );
        /* } */
        /* cout<<'\n'; */
    }

}