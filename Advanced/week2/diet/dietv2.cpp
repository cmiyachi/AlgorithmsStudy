#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;


vector<vector<double>> SetSimplex( vector<double> maxFunction, 
       vector<vector<double>> A, 
       vector<double> b)
{
 vector<vector<double>> simplex;


 int numVariables = maxFunction.size();
 int numEquations = A.size();
 int numCols = numVariables + numEquations + 1 + 1;


 for(int iRow = 0; iRow < numEquations; iRow++)
 {
  vector<double> row(numCols, 0);
  for(int iCol = 0; iCol < numVariables; iCol++)
  {
   row[iCol] = A[iRow][iCol];
  }
  row[numVariables + iRow] = 1;
  row[numCols - 1] = b[iRow];


  simplex.push_back( row );
 }


 vector<double> lastRow(numCols, 0);
 for(int iVar = 0; iVar < numVariables; iVar++)
 {
  lastRow[iVar] = 0 - maxFunction[iVar];
 }
 lastRow[numVariables + numEquations] = 1;
 simplex.push_back(lastRow);


 return simplex;
}





bool GetPivots(vector<vector<double>> simplex, int & pivotCol, int & pivotRow, bool & noSolution)
{
 int numRows = simplex.size();
 int numCols = simplex[0].size();
 int numVariables = numCols - numRows - 1;


 noSolution = false;


 double min = 0;
 for(int iCol = 0; iCol < numCols - 2; iCol++)
 {
  double value = simplex[numRows - 1][iCol];
  if(value < min)
  {
   pivotCol = iCol;
   min = value;
  }
 }


 if(min == 0)
  return false;


 double minRatio = 0.0;
 bool first = true;
 for(int iRow = 0; iRow < numRows - 1; iRow++)
 {
  double value = simplex[iRow][pivotCol];
  
  if(value > 0.0)
  {
   double colValue = simplex[iRow][numCols - 1];
   double ratio = colValue / value;


   if((first || ratio < minRatio) && ratio >= 0.0)
   {
    minRatio = ratio;
    pivotRow = iRow;
    first = false;
   }
  }
 }


 noSolution = first;
 return !noSolution;
}


vector<double> DoSimplex(vector<vector<double>> simplex, double & max)
{
 int pivotCol, pivotRow;
 int numRows = simplex.size();
 int numCols = simplex[0].size();


 bool noSolution = false;
 while( GetPivots(simplex, pivotCol, pivotRow, noSolution) )
 {
  double pivot = simplex[pivotRow][pivotCol];
  
  for(int iCol = 0; iCol < numCols; iCol++)
  {
   simplex[pivotRow][iCol] /= pivot;
  }


  for(int iRow = 0; iRow < numRows; iRow++)
  {
   if(iRow != pivotRow)
   {
    double ratio =  -1 * simplex[iRow][pivotCol];
    for(int iCol = 0; iCol < numCols; iCol++)
    {
     simplex[iRow][iCol] = simplex[pivotRow][iCol] * ratio + simplex[iRow][iCol];
    }
   }
  }
 }


 if(noSolution)
 {
  vector<double> vec;
  std::cout << "No SOLUTION!"; 
  return vec;
 }
 
 //optimo!!!
 max = simplex[numRows-1][numCols-1];
 int numVariables = numCols - numRows - 1;
 vector<double> x(numVariables, 0);
 
 for(int iCol = 0; iCol < numVariables; iCol++)
 {
  bool isUnit = true;
  bool first = true;
  double value;
  for(int j = 0; j < numRows; j++)
  {
   if(simplex[j][iCol] == 1.0 && first)
   {
    first = false;
    value = simplex[j][numCols - 1];
   }
   else if(simplex[j][iCol] != 0.0)
   {
    isUnit = false;
   }
  }


  if(isUnit && !first)
   x[iCol] = value;
  else
   x[iCol] = 0.0;
 }


 return x;
}
string cleanSpaces(string str)
{
 string space = " ";
 int pos;
 while((pos = str.find(space)) != string::npos)
 {
  str = str.erase(pos, 1);
 }
 return str;
}


vector<double> commaSeparatedStringToDoubleVector(string str)
{
 vector<double> vec;
 while(str.length() > 0)
 {
  int pos = str.find(",");
  if (pos!=string::npos)
  {
   string strNum = str.substr(0, pos);
   strNum = cleanSpaces(strNum);
   vec.push_back(atof(strNum.c_str()));
   str = str.substr(pos+1);
  }
  else
  {
   string strNum = cleanSpaces(str.c_str());
   vec.push_back(atof(strNum.c_str()));
   break;
  }
 }
 return vec;
}

void Run1()
{
               //     x1    x2     x3
 string maxFuncStr = "8.0 , 10.0 , 7.0";
 vector<double> maxFunc = commaSeparatedStringToDoubleVector(maxFuncStr);

 vector<vector<double>> A;
                                      //         x1     x2    x3
 A.push_back(commaSeparatedStringToDoubleVector("1.0 , 3.0 , 2.0"));
 A.push_back(commaSeparatedStringToDoubleVector("1.0 , 5.0 , 1.0"));
 
             //  b1     b2
 string bStr = "10.0 , 8.0";
 vector<double> b = commaSeparatedStringToDoubleVector(bStr);

 vector<vector<double>> simplex = SetSimplex(maxFunc, A, b);

 double max;
 vector<double> result = DoSimplex(simplex, max);

 printf("Result: Max = %f\n", max);
 for(int i = 0; i < result.size(); i++)
 {
  printf("x%d = %f ; ", i, result[i]);
 }
 printf("\n----------------------\n");
}



void Run2()
{
         //           x1    x2    x3    x4
 string maxFuncStr = "0.5 , 3.0 , 1.0 , 4.0";
 vector<double> maxFunc = commaSeparatedStringToDoubleVector(maxFuncStr);

 vector<vector<double>> A;
                                         //       x1     x2    x3    x4
 A.push_back(commaSeparatedStringToDoubleVector(" 1.0 ,  1.0 , 1.0 ,  1.0"));
 A.push_back(commaSeparatedStringToDoubleVector("-2.0 , -1.0 , 1.0 ,  1.0"));
 A.push_back(commaSeparatedStringToDoubleVector(" 0.0 ,  1.0 , 0.0 , -1.0"));

             //  b1     b2     b3
 string bStr = "40.0 , 10.0 , 10.0";
 vector<double> b = commaSeparatedStringToDoubleVector(bStr);

 vector<vector<double>> simplex = SetSimplex(maxFunc, A, b);

 double max;
 vector<double> result = DoSimplex(simplex, max);

 printf("Result: Max = %f\n", max);
 for(int i = 0; i < result.size(); i++)
 {
  printf("x%d = %f ; ", i, result[i]);
 }
 printf("\n----------------------\n");
}

void Run3()
{
    // 3 restrictions 2 dishes
         //           x1    x2    
 string maxFuncStr = "-1.0 , 2.0 ";
 vector<double> maxFunc = commaSeparatedStringToDoubleVector(maxFuncStr);

 vector<vector<double>> A;
                                         //       x1     x2    
 A.push_back(commaSeparatedStringToDoubleVector(" -1.0 ,  -1.0 "));
 A.push_back(commaSeparatedStringToDoubleVector("1.0 , 0.0 "));
 A.push_back(commaSeparatedStringToDoubleVector(" 0.0 ,  1.0 "));

             //  b1     b2     b3
 string bStr = "-1.0 , 2.0 , 2.0";
 vector<double> b = commaSeparatedStringToDoubleVector(bStr);

 vector<vector<double>> simplex = SetSimplex(maxFunc, A, b);

 double max;
 vector<double> result = DoSimplex(simplex, max);

 printf("Result: Max = %f\n", max);
 for(int i = 0; i < result.size(); i++)
 {
  printf("x%d = %f ; ", i, result[i]);
 }
 printf("\n----------------------\n");
}

void Run4()
{
    // 2 restrictions 2 dishes
         //           x1    x2    
 string maxFuncStr = "1.0 , 1.0 ";
 vector<double> maxFunc = commaSeparatedStringToDoubleVector(maxFuncStr);

 vector<vector<double>> A;
                                         //       x1     x2    
 A.push_back(commaSeparatedStringToDoubleVector(" 1.0 ,  1.0 "));
 A.push_back(commaSeparatedStringToDoubleVector("-1.0 , -1.0 "));


             //  b1     b2   
 string bStr = "1.0 , -2.0";
 vector<double> b = commaSeparatedStringToDoubleVector(bStr);

 vector<vector<double>> simplex = SetSimplex(maxFunc, A, b);

 double max;
 vector<double> result = DoSimplex(simplex, max);

 printf("Result: Max = %f\n", max);
 for(int i = 0; i < result.size(); i++)
 {
  printf("x%d = %f ; ", i, result[i]);
 }
 printf("\n----------------------\n");
}


void Run5()
{
    // 1 restrictions 3 dishes
         //           x1    x2    
 string maxFuncStr = "1.0 , 1.0, 1.0 ";
 vector<double> maxFunc = commaSeparatedStringToDoubleVector(maxFuncStr);

 vector<vector<double>> A;
                                         //       x1     x2    
 A.push_back(commaSeparatedStringToDoubleVector(" 0.0 ,  0.0, 1.0 "));


             //  b1     b2     b3
 string bStr = "3.0";
 vector<double> b = commaSeparatedStringToDoubleVector(bStr);

 vector<vector<double>> simplex = SetSimplex(maxFunc, A, b);

 double max;
 vector<double> result = DoSimplex(simplex, max);

 printf("Result: Max = %f\n", max);
 for(int i = 0; i < result.size(); i++)
 {
  printf("x%d = %f ; ", i, result[i]);
 }
 printf("\n----------------------\n");
}
int main ()
{
 Run1();
 Run2();
 Run3();
 Run4();
 Run5();
}
