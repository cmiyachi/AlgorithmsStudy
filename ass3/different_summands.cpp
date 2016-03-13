#include <iostream>
#include <vector>
#include <numeric>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  // 1 is always the first part of summands
 // summands.push_back(1); 
  // std::cout << summands[0] << " 0 " << '\n'; 
  int last_summand = 1; 
  
  while (true)
  {
      // loop until the summands equal n
    int sum_of_elements = 0;
    sum_of_elements = std::accumulate(summands.begin(), summands.end(), 0);
    if (sum_of_elements == n)
        break;
    // subtract the summ of the vector from n
    int current_no = n - sum_of_elements; 
    // is n >= 2*l? if so the l is the final summan
    if (current_no < last_summand + (last_summand+1))
    {
        summands.push_back(current_no);
        // std::cout << current_no << " current_no " << '\n'; 
    }
    else
        // otherwise get the maximum summand and then pick the next number
    {
        
        summands.push_back(last_summand);
        // std::cout << last_summand << " last summand " << '\n'; 
        last_summand++; 
    }
  }

  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
