#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using std::vector;
using std::cin;
using std::cout;
using namespace std;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  
 struct compare  
 {  
   bool operator()(const pair<long long, int> & l, const pair<long long, int> & r)  
   {  
        if (l.first == r.first)
            return l.second > r.second;
        else
            return l.first > r.first;  
   }  
 };  

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
      cout << " next free time " << next_free_time[next_worker]  << " nw " << next_worker << " st " << start_times_[i] << " i " << i << std::endl; 
    }
  }
  
  

 
  void AssignJobs2() {
    // set up workers thread vector
    assigned_workers_.resize(jobs_.size());
    // initialize all the start times of the jobs
    start_times_.resize(jobs_.size());
    // initialize the next free time 
    vector<long long> next_free_time(num_workers_, 0);
       
    // special case:: if the worker thread are greater than the number of jobs, they all start immediately and we are done
    if (num_workers_ > jobs_.size())
    {
        for (int i = 0; i < jobs_.size(); ++i)
        {
            assigned_workers_[i] = i;
            start_times_[i] = 0;
        }
        return;
    }
    
    // create a priority queue for the next free time
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, compare > pq;
    for (int j = 0; j < num_workers_; ++j) {
        pq.push(make_pair((long long )0, j)); // next_free_time[j]);
    }
    
    // now do all the work for computing the times the jobs start
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      
      pair<long long, int> top_p = pq.top(); 
      long long starting_time = top_p.first; 
      next_worker = top_p.second; 
      pq.pop(); // remove it from the queue 
      // cout << " start " << starting_time << std::endl; 
      
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
   
      pq.push(make_pair(next_free_time[next_worker], next_worker)); 
      // cout << " next free time " << next_free_time[next_worker]  << " nw " << next_worker << " st " << start_times_[i] << " i " << i << std::endl; 
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs2();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
