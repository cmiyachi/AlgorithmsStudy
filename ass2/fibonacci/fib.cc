#include <iostream>

int calc_fib(int n) {
    if (n <= 1)
        return n;
    
    int fibTable[n];
    fibTable[0] = 0;
    fibTable[1] = 1;
    
    for (int i = 2;i<= n; i++)
        fibTable[i] = fibTable[i-1]+fibTable[i-2];
    
    return fibTable[n]; 
}

int main() {
    int n = 0;
    std::cin >> n;

    std::cout << calc_fib(n) << '\n';
    return 0;
}
