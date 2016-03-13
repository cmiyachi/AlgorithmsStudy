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

main(){
	int n, m;
	while (cin >> n >> m)
	cout << fib(n,m) << endl;
}