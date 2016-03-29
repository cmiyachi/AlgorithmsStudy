#include <iostream>
#include <vector>
#include <random>
#include <map> 
#include <set>



using std::vector;
using std::swap;
using std::map; 
using std::multimap;
using std::multiset;
using std::pair;

/*
The goal in this problem is given a set of segments on a line and a set of points on a line, to count, for each
point, the number of segments which contain it.
Problem Description
Task. In this problem you are given a set of points on a line and a set of segments on a line. The goal is to
compute, for each point, the number of segments that contain this point.
*/ 


vector<int> faster_count_segments(vector<int> starts, vector<int> ends, vector<int> points)
{
    // multimap<int,char> sorted_seg_points;
    multiset<pair<int, char>> sorted_seg_points;
    multimap<int, int> point_count; 
    vector<int> cnt(points.size());
    
    for (size_t i = 0; i < starts.size(); i++)
    {
        sorted_seg_points.insert (std::make_pair(starts[i], 'l'));
        sorted_seg_points.insert (std::make_pair(ends[i], 'r'));
    }
    for (size_t i = 0; i < points.size(); i++)
    {
        sorted_seg_points.insert (std::make_pair(points[i], 'p'));
    }
    
    int count = 0; 
    // this map is sorted in ascending order
    /*  for(auto it = sorted_seg_points.cbegin(); it != sorted_seg_points.cend(); ++it)
    {
       std::cout << it->first << " " << it->second << "\n";
    } */
    for(auto it = sorted_seg_points.cbegin(); it != sorted_seg_points.cend(); ++it)
    {
       // std::cout << it->first << " " << it->second << "\n";
       if (it->second == 'l')
           count++;
       else if (it->second == 'p')
       {
            point_count.insert (std::make_pair(it->first, count));
           // count = 0; 
       }
       else if (it->second == 'r')
       {
         //  if (count > 0)
            count--; 
       }
    }
    
    // create the cnt vector
    for (size_t i = 0; i < points.size(); i++)
        cnt[i] = point_count.find(points[i])->second;
        
    return cnt;
}



/* 

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
} */

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
 /*  vector<int> cnt = naive_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  } */
  
  //use fast_count_segments
  vector<int> cnt = faster_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
