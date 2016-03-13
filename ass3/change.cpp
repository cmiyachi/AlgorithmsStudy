#include <iostream>
// Greedy algorithm for getting change 
int get_change(int n) {
  int coins[3] = {10,5,1}; //sorted from highest to lowest
  int value = n;
  int count = 0;
  int m; 

for (int i = 0; i < 3 ; i++ )
  {
      while (value >= coins[i])
      {
          value = value - coins[i];
          count++;
 
      }
      if (value == 0) break;
  }
  return count;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << get_change(n) << '\n';
}
