#include <iostream>
#include <vector>
#include <algorithm>
// In this problem you will convert an array of integers into a heap.

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int Parent(int i)
  {
      int new_i = floor((i-1)/2); 
      return new_i; 
  }
  
  int LeftChild(int i)
  {
      int new_i = 2*i +1;
      return new_i;
  }
  
  int RightChild(int i)
  {
      int new_i = (2*i +2);
      return new_i;
  }
  
  void SiftUp(int i)
  {
      while (( i > 0) && (data_[Parent(i)] < data_[i]))
      {
          int p_i = Parent(i); 
          swap(data_[p_i],data_[i]);     
          cout << p_i << " " << i << std::endl; 
          i = Parent(i);
      }          
      
  }
  
  void SiftDown(int i)
  {
      int maxIndex = i;
      int l = LeftChild(i);

      if ((l < data_.size()) && (data_[l] < data_[maxIndex]))
          maxIndex = l;
      int r = RightChild(i);

      if ((r < data_.size()) && (data_[r] <  data_[maxIndex]))
          maxIndex = r;
      if (i != maxIndex)
      {
          swap(data_[i], data_[maxIndex]);
          swaps_.push_back(make_pair(i,maxIndex)); 
          SiftDown(maxIndex);
      }
  }
  void GenerateSwaps() {

    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    /* for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      } */
      for (int i = (floor(data_.size()/2)-1); i >= 0; i--)
      {
          SiftDown(i); 
      }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
