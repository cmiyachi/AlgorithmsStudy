#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


string InverseBWT(const string& bwt) {
  string text = bwt;


  // write your code here
  string result = "";
  result.resize(text.length());
  vector<int> first_column(text.length(), 0); 
  vector<int> last_column(text.length(), 0); 

  
  string column1 = text;
  sort(column1.begin(), column1.end());
  // cout << column1 << endl;
  
  int aindex=0, gindex=0, tindex=0, cindex = 0;
  // create the indices
  for (int i = 0; i < text.length(); i++)
  {
      char clast = text[i];
      if (clast == 'A')
        last_column[i] = ++aindex;
      else if (clast == 'G')
          last_column[i] = ++gindex;
      else if (clast == 'T')
          last_column[i] = ++tindex;
      else if (clast =='C')
          last_column[i] = ++cindex;
      else if (clast == '$')
          last_column[i] = 1; // there is always only 1
          
  }
  
  aindex=0, gindex=0, tindex=0, cindex = 0;
   for (int i = 0; i < column1.length(); i++)
  {
      char cfirst = column1[i];
      if (cfirst == 'A')
        first_column[i] = ++aindex;
      else if (cfirst == 'G')
          first_column[i] = ++gindex;
      else if (cfirst == 'T')
          first_column[i] = ++tindex;
      else if (cfirst =='C')
          first_column[i] = ++cindex;
      else if (cfirst == '$')
          first_column[i] = 1; // there is always only 1
  }
  
  // construct the first row of the matrix
  // first what position of the string the $ is in the last column1
  size_t pos = text.find("$");
  // cout << "pos " << pos << endl;
  
  for (int i = 1; i < text.length(); i++)
  {
      char c = result[i-1] = column1[pos];
      int index = first_column[pos];
      // cout << " index " << c << " " << index << endl;
      pos = -1; 
      for (int j = 0; j < index; j++)
      {
          pos = text.find(c, ++pos);
      }
       // cout << "pos after " << pos << endl;
  }
  // put the ending on the string
  result[text.length()-1] = '$';
  
  return result;

}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
