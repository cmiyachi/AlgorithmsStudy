#include <map>
#include <iostream>
using namespace std;


#define long long long
const long M = 1000000; // modulo
long my_mod = 1; 
map<long, long> F;



long f(long n) {
	if (F.count(n)) return F[n];
	long k=n/2;
	if (n%2==0) { // n=2*k
		return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % M;
	} else { // n=2*k+1
		return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % M;
	}
}

/* long f(long n) {
    if (n < 2) {
        return F[n]; // F[] for memoization
    }
    if (n > 1 && F[n] != 0) { 
        return F[n]; // if F[n] is already calculated
    }
    // if n is odd, use the next one
    long k = (n % 2 == 0)? n/2 : (n+1) / 2;

    // the formula from wikipedia
    F[2*k-1] =  ((f(k)*f(k) + f(k-1)*f(k-1)))% M;
    F[2*k] = ((2*f(k-1) + f(k)) * f(k)) % M;
    return F[n];
} */


// compute the pisano period for any number
 long pisano( long m) {
   long result = 2;
  for (
     long fn2 = 1, fn1 = 2%m, fn = 3%m;
    fn1 != 1 || fn != 1;
    fn2 = fn1, fn1 = fn, fn = (fn1 + fn2)%m
  ) {
    result++;
  }
  return result;
}
long get_fibonaccihuge( long n,  long m) {
  // find the pisano number
   long piz_no = pisano(m);
   long fib_to_find = n % piz_no;
    cout << "\npisano = " << piz_no << "\n";
    cout << "\nfib_to_find = " << fib_to_find << "\n";
  // find the fibinancci number of this smaller number for modulo of large one
  long fib_no  = 0;
  if (fib_to_find != 0)
      fib_no = f(fib_to_find-1);
   cout << "fib no " <<  fib_no << endl;
  return (fib_no%m);
}
int main() {
    long n, m;
    my_mod = m; 
    
    std::cin >> n >> m;
    
    
    F[0]=F[1]=1;

    std::cout << get_fibonaccihuge(n, m) << '\n';
}
