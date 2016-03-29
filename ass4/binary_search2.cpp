#include <iostream>
#include <cassert>
#include <vector>

/*
The goal in this code problem is to implement the binary search algorithm.  Started using vectors but large test cases ran too slow
So I had to use regular arrays and pass the array size. 

*/ 
using std::vector;

int binary_search(int a[], int a_size, int x) {
   // const int a_size = a.size(); 
  int left = 0, right = a_size;  
 // std::cout << " left " << left << " right " << right << " x " << x << "\n"; 

  
 

  if (right - left <= 2)
  {
      /* std::cout << "only 2\n";  */
    
      // only two left
      if (x == a[left]) 
      {
          // std::cout << " L " << left << "\n"; 
          return left;
      }
      else if (x == a[right-1])
      {
          // std::cout << " R " << right-1 << "\n"; 
          return (right-1);
      }
      else
      {
          // std::cout << "no solution";
          return -1;  // solution not found
      }
      /* std::cout << "\n"; */
  }
  
 
  int mid = left + (right-left)/2; 
    // std::cout << "mid " << mid << "\n"; 

  
  if (x == a[mid])
      return mid;
  else if (x < a[mid])
  {
     // vector<int> Aa(a.begin(), a.begin() + mid); 
	 // int Aa[mid];
	 // std::copy(a, a+mid, Aa); 
     /*  for (size_t i = 0; i < Aa.size(); i++) {
            std::cout <<  " less " << Aa[i] << " size " << Aa.size() << "\n"; 
      }  */
      return binary_search(a,mid, x);
  } 
  else
  {
     int second_half = a_size -(mid+1); 
     //vector<int> Aa(a.begin()+mid+1, a.begin() + a_size); 
	// 	  int Aa[second_half];
	//  std::copy(a+mid+1, a+a_size, Aa); 
    /*  for (size_t i = 0; i < Aa.size(); i++) {
            std::cout <<  " greater " << Aa[i] << " size " << Aa.size() << "\n"; 
        }  */
		
	
    int ans = binary_search((a+mid+1), second_half, x);
    if ( ans != -1 )
        return (ans + (mid+1));
    else return (-1); 
  }
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);


  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  
	int* aa = &a[0];
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search(aa, n, b[i]) << ' ';
  }
}
