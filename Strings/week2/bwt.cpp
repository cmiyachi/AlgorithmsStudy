#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string leftRotatebyOne(const string& text)
{
    int n = text.length();
    int i;
    char temp;
    temp = text[0];
    string new_text;
    new_text.resize(text.length());
    for (i = 0; i < n-1; i++)
      new_text[i] = text[i+1];
    new_text[i] = temp;
    return new_text;
}

string BWT(const string& text) {
  string result = "";
  vector<string> bwt_matrix;

  // write your code here
  string next_string = text;
  for (int i; i < text.length(); i++)
  {
      bwt_matrix.push_back(next_string);
      next_string = leftRotatebyOne(next_string);
      // cout << next_string << endl;
  }
  // sort the vector
  result.resize(bwt_matrix.size());
  sort(bwt_matrix.begin(),bwt_matrix.end()); //Use the start and end like this
  for (int i = 0; i < bwt_matrix.size(); i++)
  {
      // cout << bwt_matrix[i] << endl;
      result[i] = bwt_matrix[i][text.length()-1];
  }
  
  // grab the last column of matrix
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}