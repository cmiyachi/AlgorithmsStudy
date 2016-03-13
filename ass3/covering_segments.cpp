#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  // Sort the line segments so that the lowest right /end point is the first in array
  for (size_t i = 0; i < segments.size(); ++i)
  {
	  for (size_t j = i+1; j < segments.size(); ++j)
	  {
		  if (segments[i].end > segments[j].end)
		  {
			 // std::cout << "i " << i << " j " << j << "seg " <<segments[i].end << " j end " << segments[j].end << "\n"; 
			  Segment temp;
			  temp.start = segments[j].start;
			  temp.end = segments[j].end;
			  segments[j].start = segments[i].start;
			  segments[j].end = segments[i].end;
			  segments[i].start = temp.start;
			  segments[i].end = temp.end;
		  }
	  }
  }
  
  // pick the right most point as the safe choice
   for (size_t i = 0; i < segments.size(); ++i)
  {
	  // select the first safe choice
	  points.push_back(segments[i].end);
	  int curr_point = segments[i].end;
	  // is this point in the next segment?
	  for (size_t j = i+1; j < segments.size(); ++j)
	  {
		//  std::cout << "i " << i << " j " << j << " curr " << curr_point << " seg " <<segments[j].start << " j end " << segments[j].end << "\n"; 
		 if ((curr_point <= segments[j].end) && (curr_point >= segments[j].start))
		 {
			 i++; 
		
		 }	
		else
		{
			break;
		}
	  }
	  
  }
/*   for (size_t i = 0; i < segments.size(); ++i) {
    points.push_back(segments[i].start);
    points.push_back(segments[i].end);
  } */
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
