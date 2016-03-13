#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 2
#define int long long


void mult(int a[MAXN][MAXN], int b[MAXN][MAXN], int c[MAXN][MAXN], int mod) {
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      a[i][j] = 0;
      for (int k = 0; k < MAXN; k++) {
        a[i][j] = (a[i][j] + (uint64_t(b[i][k])*c[k][j])%mod)%mod;
      }
    }
  }
}
void exp_by_sqr(int mat[MAXN][MAXN], int power, int mod) {
  // base = mat;
  int base[MAXN][MAXN], tmp[MAXN][MAXN];
  memcpy(base, mat, sizeof(base));
  
  // mat starts with the identity matrix
  memset(mat, 0, sizeof(base));
  for (int i = 0; i < MAXN; i++) {
    mat[i][i] = 1;
  }
  
  // while power is not zero
  while (power) {
    if (power & 0x1) { // if power is odd
      memcpy(tmp, mat, sizeof(tmp));
      mult(mat, tmp, base, mod); // mat *= base;
    }
    memcpy(tmp, base, sizeof(tmp));
    mult(base, tmp, tmp, mod); // base *= base;
    power >>= 1; // power = power/2;
  }
}
int fib(int n, int mod) {
  if (n == 0) {
    return 0;
  }
  int mat[2][2] = {
    {1, 1},
    {1, 0}
  };
  exp_by_sqr(mat, n - 1, mod);
  return mat[0][0];
}
// compute the pisano period for any number
 int pisano( int m) {
   int result = 2;
  for (
     int fn2 = 1, fn1 = 2%m, fn = 3%m;
    fn1 != 1 || fn != 1;
    fn2 = fn1, fn1 = fn, fn = (fn1 + fn2)%m
  ) {
    result++;
  }
  return result;
}
int get_fibonaccihuge( int n,  int m) {
  // find the pisano number
   int piz_no = pisano(m);
   int fib_to_find = n % piz_no;
  // cout << "\npisano = " << piz_no << "\n";
  // cout << "\nfib_to_find = " << fib_to_find << "\n";
  // find the fibinancci number of this smaller number for modulo of large one
  int fib_no  = 0;
  if (fib_to_find != 0)
      fib_no = fib(fib_to_find, m);
 //  cout << "fib no " <<  fib_no << endl;

  return (fib_no);
}
main(){
	int n, m;
	while (cin >> n >> m)
    {
       // cout << fib(n,m) << endl;
        cout << get_fibonaccihuge(n,m) << endl;
      //  cout << get_fibonaccihuge(n,m)%m << endl;
    }
}