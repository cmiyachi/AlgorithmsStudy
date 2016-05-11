#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;



class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector <int> results; 

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);

    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }
  
 void traverse_in_order(int index)
 {
     if (index != -1)
     {
         traverse_in_order(left[index]);
         results.push_back(key[index]);
         traverse_in_order(right[index]);
     }
 }
 
 void traverse_pre_order(int index)
 {
     if (index != -1)
     {
         results.push_back(key[index]);
         traverse_pre_order(left[index]);
         traverse_pre_order(right[index]);
     }
 }
 void traverse_post_order(int index)
 {
     if (index != -1)
     {
         traverse_post_order(left[index]);
         traverse_post_order(right[index]);
         results.push_back(key[index]);
     }
 }
  vector <int> in_order() {
   results.clear(); 
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_in_order(0);
    return results;
  }

  vector <int> pre_order() {
    results.clear();    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_pre_order(0);
    return results;
  }

  vector <int> post_order() {
   results.clear(); 
    // Finish the implementation
    // You may need to add a new recursive method to do that
    traverse_post_order(0);
    return results;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}
