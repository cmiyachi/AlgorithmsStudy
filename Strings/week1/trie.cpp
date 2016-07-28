#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>  

using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(vector<string> & patterns) {
  trie t;
   // t.resize(t.size()+1);
 
 bool match_found = false; 
 std::map<char,int>::iterator it;
 
   edges ne; // = stdmap<char,int>;
   t.push_back(ne);
   
  // for each string Pattern in patterns
  for (int i = 0; i < patterns.size(); i++)
  {
      string currentPattern = patterns[i];
      int current_node = 0;
    
      
      
      for (int j = 0; j < currentPattern.length(); j++ )
      {
          char  currentSymbol = currentPattern[j]; 
           match_found = false;
/*           cout << currentSymbol << endl;
          cout << "size " << t.size() << endl; */
          // if there is an outgoing edge from current node with label current symbol
          if (t.size() >= current_node)
          {
               edges ee = t[current_node];
              // cout << "e size " << ee.size() << " curr node " << current_node << endl;
              // get all edges outgoing of current node
              for (int k = 0; k < ee.size(); k++)
              {
                  
                  it = ee.find(currentSymbol);
                  if (it != ee.end())
                  {
                      match_found = true;
                      current_node = it->second;
                      // cout << "match " << current_node << endl;
                    //  break;
                  }
              }
          }
          if (!match_found)
          {
              // add new node to trie
              int new_node = t.size();
             
              // cout << "resize " << t.size() << endl;
             edges e;
              if (t.size() > 0)
                e = t[current_node]; 
              /*  for (const auto & j : e) {
                  std::cout << current_node << "B->" << j.second << ":" << j.first << "\n";
                } */
              e.insert(std::pair<char,int>(currentSymbol,new_node));
            /*    for (const auto & j : e) {
                  std::cout << current_node << "->" << j.second << ":" << j.first << "\n";
                } */
              // t.at(current_node) = e; 
              std::vector<edges>::iterator it = t.begin();
              /* std::vector<edges>::iterator it_end = t.begin();
              std::advance(it,current_node);
                std::advance(it_end,current_node+1); */
             // std::replace(it, it_end, "old", "new");
             *(it+current_node) = e; 
              current_node = new_node; 
              // t.resize(t.size()+1);
              t.push_back(ne);
              // cout << "no match " << current_node << endl;
              /* for (size_t i = 0; i < t.size(); ++i) {
                for (const auto & j : t[i]) {
                  std::cout << i << "->" << j.second << ":" << j.first << "\n";
                }
              } */
          }
      }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}