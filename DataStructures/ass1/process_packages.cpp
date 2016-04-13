#include <iostream>
#include <deque>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {
        
    }

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {
        // std::cout << "buffer created with size " << size << "  " << size_ << "\n";
    }

    Response Process(const Request &request) 
    {
        Response response(false, 0);
        // clear out anything that is done
        // request time arrival is it >= finish time?  Then pop these finish times
        int now = request.arrival_time; 
        int ftime = now + request.process_time; 
        // std::cout << " now ftime " << now << " " << ftime << " size " << finish_time_.size() << std::endl; 
        // iterate through queue to see if finish time <= now and if so pop it
        for (int i = 0; i < finish_time_.size(); i++) // :finish_time_) 
        {
            // std::cout << "dequ_ftime " << finish_time_[i] << "\n"; 
            if (now >= finish_time_[i])
                finish_time_.pop_front(); 
            else if (now < finish_time_[i])
                break;
        }
        
        // std::cout << " adding something ? \n"; 
        // is there space in the buffer? If not not , set -1
        if (finish_time_.size() >= size_)
        {
            // std::cout << "no space\n"; 
            response.dropped = true;
            response.start_time = -1; 
        }
        else // can this request start processing?  If so set finish time
        {
            int last_finish_time = 0; 
            if (finish_time_.size() > 0)
            {
                last_finish_time = finish_time_.back();
            }
            int new_finish_time = 0; 
            int update_start_time = now; 
            // std::cout << "inside " << last_finish_time << std::endl; 
            if (now > last_finish_time)
            {
                new_finish_time = ftime; 
                update_start_time = now; 
                // std::cout << "greater " << new_finish_time << " " << update_start_time << std::endl; 
            }
            else
            {
                new_finish_time = last_finish_time + request.process_time;
                update_start_time = last_finish_time; 
                // std::cout << "else " << new_finish_time << " " << update_start_time << std::endl; 
            }
            finish_time_.push_back(new_finish_time); 
            response.start_time = update_start_time;
            response.dropped = false; 
        }
       return response; 
    }
    
private:
    int size_;
    std::deque <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    
    if (size <= 0) return 0;
    
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
