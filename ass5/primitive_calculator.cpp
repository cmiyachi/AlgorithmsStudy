#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min; 

vector<int> optimal_sequence_naive(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}


vector<int> optimal_sequenceDP(int n) {

    std::vector<int> sequence;
    int arr[n+1]; arr[1]=0;
    int i,temp;

    for(i=2;i<=n;i++){
        arr[i]=1+arr[i-1];
        if(i%2==0) arr[i]=min(arr[i],1+arr[i/2]);
        if(i%3==0) arr[i]=min(arr[i],1+arr[i/3]);
        temp=arr[i];
    }

    while(n>=1 && temp>=0){
        sequence.push_back(n);

        /* if(n==10){
            n=n-1;
            temp--;
        }
        else */ if(n%2 == 0){
            n=n/2;
            temp--;
        }
        else if(n%3 == 0){
            n=n/3;
            temp--;
        }
        else{
            n=n-1;
            temp--;
        }
    }

    reverse(sequence.begin(), sequence.end());

    return sequence;
}
int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequenceDP(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
