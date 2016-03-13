#include <iostream>

int gcd(int a, int b) {
  //write your code here
  if (b == 0)
      return a;
  else
      gcd(b,a%b);
}

long long lcm(int a, int b) {
  //write your code here
  int my_gcd = gcd(a,b); 
 //  std::cout << "my gcd " << my_gcd << "\n"; 
  long long ab = (long long )a* (long long)b;
  // std::cout << " a * b = " << ab << "\n"; 
  return ((ab)/my_gcd);
  // return ((a*b)/gcd(a,b));
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
