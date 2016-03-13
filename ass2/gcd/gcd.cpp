#include <iostream>

int gcd(int a, int b) {
  //write your code here
  if (b == 0)
      return a;
  else
      gcd(b,a%b);

}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
