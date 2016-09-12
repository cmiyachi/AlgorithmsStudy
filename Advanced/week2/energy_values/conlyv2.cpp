#include<stdio.h>
#include <iostream>

const double EPS = 1e-6;
const int PRECISION = 20;

int main()
{
    int i,j,k,n;
    double A[21][21],c,x[21],sum=0.0;
    // printf("\nEnter the order of matrix: ");
    // scanf("%d",&n);
    // printf("\nEnter the elements of augmented matrix row-wise:\n\n");
    // for(i=1; i<=n; i++)
    // {
        // for(j=1; j<=(n+1); j++)
        // {
            // printf("A[%d][%d] : ", i,j);
            // scanf("%f",&A[i][j]);
        // }
    // }
    
    int size;
    std::cin >> size;
    n = size; 
    // for (int row = 1; row <= size; ++row) {
        // for (int column = 1; column < (size+1); ++column)
            // std::cin >> A[row][column];
       // std::cin >> b[row];
    // }
    
    
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n+1); j++)
        {
            scanf("%g",&A[i][j]);
        }
    }
    
    for(j=1; j<=n; j++) /* loop for the generation of upper triangular matrix*/
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
     std::cout.precision(PRECISION);
    for(i=1; i<=n; i++)
    {
        // printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
        std::cout << x[i] << std::endl;
    }
    return(0);
}