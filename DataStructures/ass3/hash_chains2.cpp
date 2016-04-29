#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using std::string;
using std::vector;
using std::cin;
using std::map; 
using std::endl; 
using std::pair;
using std::cout; 

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    // vector<string> elems;
    map<int, vector<string>> elems;
    
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    
    void processQuery(const Query& query) {
        
       
       
        
        if (query.type == "check") {
           vector<string> these_strings = elems[query.ind];
           
           /*  cout << "CHECK size " << these_strings.size() << endl; 
            for (int i = static_cast<int>(these_strings.size()) - 1; i >= 0; --i)
            {
                std::cout << " *** " << these_strings[i] << " *** \n ";
            } */
            
            for (int i = static_cast<int>(these_strings.size()) - 1; i >= 0; --i)
            {
                std::cout << these_strings[i] << " ";
            }
            std::cout << "\n";
        } else {
            int hf = hash_func(query.s);
            vector<string> these_strings = elems[hf];
            vector<string>::iterator it = std::find(these_strings.begin(), these_strings.end(), query.s);
            // cout << "ELSE size " << these_strings.size() << endl; 
/*             for (int i = static_cast<int>(these_strings.size()) - 1; i >= 0; --i)
            {
                std::cout << " *** " << these_strings[i] << " *** \n ";
            }
            */
            if (query.type == "find")
            {
                writeSearchResult(it != these_strings.end());
            }
            else if (query.type == "add") {
                if (it == these_strings.end())
                {
                    // cout << " adding " << query.s << endl; 
                    these_strings.push_back(query.s);
                    elems[hf] = these_strings;
                }
                /* vector<string> these_strings = elems[hf];
                these_strings.push_back(query.s);
                elems[hf] = these_strings; 
                cout << "add " << hf << " " << query.s << "\n";  */
            } else if (query.type == "del") {
                /* vector<string> these_strings = elems[query.ind]; 
                for (int i = 0; i < these_strings.size(); i++)
                {
                    if (these_strings[i] == query.s)
                        these_strings.erase(these_strings.begin() + i); 
                } */
                if (it != these_strings.end())
                {
                    these_strings.erase(it);
                    elems[hf] = these_strings; 
                }
            }
        }
    }
    
    /*  void processQueryOld(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    } */

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
