#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

/* In this problem, your goal is to add parentheses to a given arithmetic expression to maximize its value.
Problem Description
Task. Find the maximum value of an arithmetic expression by specifying the order of applying its arithmetic
operations using additional parentheses.
*/
using std::vector;
using std::string;
using std::max;
using std::min;

struct parens {
  long long d;
  char op;
} ;

// create the min and max matrices
  long long m[1000][1000];
  long long M[1000][1000]; 
  parens _parens[100];  // problem limits to 29 symbols
  
long long find_min_val(long long final, long long a, long long b, long long c, long long d)
{
    if (a < final)
       final = a;
    if (b < final)
            final = b; 
    if (c < final)
            final = c; 
    if (c < final)
            final = c; 
        
    return final; 
}

long long find_max_val(long long final, long long a, long long b, long long c, long long d)
{
    if (a > final)
       final = a;
    if (b > final)
            final = b; 
    if (c > final)
            final = c; 
    if (c > final)
            final = c; 
        
    return final; 
}
  
long long eval(long long a, long long b, char op) {
    // std::cout << " a b op " << a << b << op << "\n"; 
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

void MinAndMax(int i, int j, long long &min, long long &max)
{
    long long min_val = 9999999999;
    long long max_val = -999999999;
    
    // std::cout <<  i << " i " << j << " j "  << "\n"; 
    
    for (int k = i; k <= (j-1); k++)
    {
        // std::cout << "in loop " << i << " i " << j << " j " <<  k << " k " << "\n"; 
        long long a, b, c, d;
        // std::cout << " op " << _parens[k].op << "\n";
        a = eval(M[i][k], M[k+1][j], _parens[k].op);
        b = eval(M[i][k], m[k+1][j], _parens[k].op);
        c = eval(m[i][k], M[k+1][j], _parens[k].op);
        d = eval(m[i][k], m[k+1][j], _parens[k].op);
        min_val = find_min_val(min_val, a,b,c,d);
        max_val = find_max_val(max_val, a, b, c, d); 
    }
    
    min = min_val;
    max = max_val; 
}

long long Parentheses(struct parens p[], int n)
{
    for (int i = 0 ; i < n+1; i++)
    {
        m[i][i] = p[i].d;
        M[i][i] = p[i].d;
    }
     for (int s = 1; s <= (n-1); s++)
        for ( int i = 0; i < (n -s); i++ )
    {
        int j = i+s;
        long long min_val, max_val;
        // std::cout << p[i].op << " op before \n"; 
        MinAndMax(i,j, min_val, max_val); 
        m[i][j] = min_val; 
        M[i][j] = max_val; 
        // std::cout << " s " << " i " << s << " " << i << " min " << min_val << " max " << max_val << "\n"; 
   
    }
    
    return M[0][n-1];
}

long long get_maximum_value(const string &exp) {
  // separate out the numbers from the operations
  // we know that each character is either a number or an operation
  int l = exp.length();
  // std::cout << " len " << l<< "\n";
  
  int n = ((l-1)/2) + 1;
  
  
  // std::cout << " n " << n<< "\n";
  char exp_array[n+1];
  strcpy(exp_array, exp.c_str()); 
  
 
  for (int j = 0, i = 0; j < n, i < l; j++, i=i+2)
   // for (int i = 0; i < l; i=i+2)
    {
        _parens[j].d = atoll(&(exp_array[i]));
        _parens[j].op = exp_array[i+1]; 
        // std::cout << "i " << i  << " j " << _parens[j].d << " " << _parens[j].op << "\n"; 
    }
  //  _parens[n-1].d = atoll(&(exp_array[l-1])); 
 //   std::cout <<  _parens[n-1].d << " " << _parens[n-1].op << "\n"; 
 long long answer = Parentheses(_parens, n);

  
  return answer;
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
