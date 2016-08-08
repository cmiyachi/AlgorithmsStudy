#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int char_to_index(char c)
{
    if (c =='A')
        return 0;
    if (c == 'C')
        return 1;
    if (c == 'G')
        return 2;
    if (c == 'T')
        return 3;
    
    return -1; 
}

string InverseBWT(const string& text) {

  // write your code here
  string result = "";
  vector<int> rank(text.length(), 0); 
  int fcol[4]; 

  
 int aindex=0, gindex=0, tindex=0, cindex = 0;
  // create the indices
  for (int i = 0; i < text.length(); i++)
  {
      char clast = text[i];
      if (clast == 'A')
        rank[i] = ++aindex;
      else if (clast == 'G')
          rank[i] = ++gindex;
      else if (clast == 'T')
         rank[i] = ++tindex;
      else if (clast =='C')
          rank[i] = ++cindex;
      else if (clast == '$')
          rank[i] = 1; // there is always only 1
  }
  
  if (aindex > 0)
    fcol[char_to_index('A')] = 1;  // A always is the first if it exists (after $)
  if (cindex > 0)
      fcol[char_to_index('C')] = aindex+1;
  if (gindex > 0)
      fcol[char_to_index('G')] = cindex+aindex+1;
  if (tindex > 0)
      fcol[char_to_index('T')] = gindex+cindex+aindex+1;
  
    // construct the first row of the matrix
 char c = text[0];
 // cout << "c " << c << endl;
 int index = 0; 
 int r = 1; 
  for (int i = 1; i < text.length(); i++)
  {
      /* cout << c; */
      // cout << "top   index  r  c " << index << " " << r << " " << c<<  endl;
      index = fcol[char_to_index(c)]+r-1;
      r = rank[index];
      // result[text.length() - i-1] = (c);
      result.insert(0,1,c);
      // compute next c
      c = text[index];
    // cout << "bottom index  r  c " << index << " " << r << " " << c<<  endl;
  }
  // put the ending on the string
  /* result[text.length()-1] =  */  /* cout << '$' << endl;; */
  result.push_back('$');
  
  return result;

}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
