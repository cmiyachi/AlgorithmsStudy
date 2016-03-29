#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
/* An inversion of a sequence a0; a1; : : : ; an􀀀1 is a pair of indices 0  i < j < n 
such that ai > aj . The
number of inversions of a sequence in some sense measures how close the sequence is to 
being sorted. For
example, a sorted (in non-descending order) sequence contains no inversions at all, 
while in a sequence sorted
in descending order any two elements constitute an inversion (for a total of n(n 􀀀 1)=2 
inversions).
The goal in this problem is to count the number of inversions of a given sequence.
*/ 
using namespace std;
typedef long long LL;
 
LL interpolate(int x[], int start, int middle, int end) {
    int i, j, k, b[end+1];
    LL c;
 
    for(i = start; i <= middle; i++) b[i] = x[i];
    for(j = end; i <= end; i++, j--) b[i] = x[j];
 
    for(c = 0, j = end, i = k = start; k <= end; k++)
        if(b[i] <= b[j])
            x[k] = b[i++];
        else {
          x[k] = b[j--];
          c = c + (middle - i + 1);
        }
 
    return c;
}
 
LL merge_sort(int x[], int start, int end) {
    int middle;
 
    if(start >= end) return 0;
    middle = (start + end) / 2;
 
    return  merge_sort(x, start, middle) +
            merge_sort(x, middle+1, end) +
            interpolate(x, start, middle, end);
}
 
/* int main() {
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Number of inversions are %lld \n", merge_sort(arr, 0, n-1));
    int t, i;
 
    return 0;
}
  */
 int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  int* aa = &a[0];

  std::cout << merge_sort(aa, 0, (a.size()-1)) <<'\n';
  
 
}