#include <iostream>
#include <vector>

using std::vector;

// globals
 int n; // size of data array

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double total_value = 0.0;
  int curr_cap = capacity;
  double x[n]; // items in knapsack
  int i = 0; // loop variable
  
  for (i = 0; i < n; i++)
      x[i] = 0.0;
  
  for (i = 0; i < n; i++)
  {
      if (weights[i] > curr_cap)
          break;
      else
      {
          x[i] = 1.0;
          total_value = total_value + values[i];
          curr_cap = curr_cap - weights[i];
      }
  }

  if (i < n)
      x[i] = (double )curr_cap/(double )weights[i];
  total_value = total_value + x[i]*values[i];

 /*  std::cout << "The result vector is \n";
  for (i = 0; i < n; i++)
      std::cout << x[i] << " " ; */
  
 /*  std::cout << "\n Max value is " <<total_value << "\n";  */
  return total_value;
}


int main() {

  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  vector<double> ratios(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }
  
  // compute the ratio so we can presort the vecotrs
  for (int i; i < n; i++)
  {
      ratios[i] = (double )values[i]/ (double )weights[i];
  }

  double dtemp = 0; 
  int itemp = 0; 
  // sort the values and weights vector
  for (int i = 0; i < n; i++)
  {
      for (int j = i+1; j < n; j++)
      {
          if (ratios[i] < ratios[j])
          {
              dtemp=ratios[j];
              ratios[j] = ratios[i];
              ratios[i] = dtemp;
              
              itemp = weights[j];
              weights[j] = weights[i];
              weights[i] = itemp;
              
              itemp = values[j];
              values[j] = values[i];
              values[i] = itemp;
          }
      }
  }
  
  /*  for (int i; i < n; i++)
  {
      std::cout << "ratioS " << i << " " << ratios[i] <<"\n"; 
      std::cout << "weights " << i << " " << weights[i] <<"\n"; 
      std::cout << "values " << i << " " << values[i] <<"\n"; 
  } */
  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
