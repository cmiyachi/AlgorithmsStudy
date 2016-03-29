#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
/* 
An element of a sequence of length n is called a majority element if it appears in the sequence strictly more
than n=2 times. Tried a divide and conquer algorithm but this is way simpler.  Also O(n) versus O(nlogn)
*/

using std::vector;
using std::map;

map<int,int> all_results;

int get_majority_element(vector<int> &a, int left, int right) {
	// for each element add up the hash table
	for (size_t i = 0; i < a.size(); ++i)
	{
		all_results[a[i]]++;
		// std::cout << " ai "  << a[i] << " ar " << all_results[a[i]] << "\n";
	}
	
	int majority_num = a.size()/2; 
	// now find the max -it must be greater or equal to majority numeric_limits
	for (size_t i = 0; i < a.size(); ++i)
	{
		if (all_results[a[i]] > majority_num)
			return a[i];
	}
	// if we reach here we have not found a majority
	return -1; 
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
