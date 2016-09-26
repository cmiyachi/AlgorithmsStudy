#include <iostream>
#include <vector>
#include <sys/resource.h>
#include <algorithm>
#include <climits>

using namespace std;

struct Vertex {
    int weight;
    std::vector <int> children;
    bool visited = false; 
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;



Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;
    Graph tree(vertices_count);
    

    for (int i = 0; i < vertices_count; ++i)
    {
        std::cin >> tree[i].weight;
    }
    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

void dfs(Graph &tree, int vertex, int parent, vector<int> &funfactor, int root) {
 
    // sum the weight of all the children
    for (int child : tree[vertex].children)
    {
        // cout << " parent " << parent <<  " vertex " << vertex << " child " << child << " weight " << tree[vertex].weight << endl; 
        if (child != parent) 
        {
            dfs(tree, child, vertex, funfactor, root);
            // cout << " sum child = " << total_children_sum << endl;
        }
        
    }
    if (funfactor[vertex] == INT_MAX)
    {
        if  ((tree[vertex].children.size() == 1) && (vertex != root))
        {
            funfactor[vertex] = tree[vertex].weight;
        }
        else
        {
            int m1 = tree[vertex].weight;
            for (int child : tree[vertex].children)
            {
                if (child != parent) {
                    for (int grandchild : tree[child].children) 
                    {
                        if (grandchild != vertex) {
                            m1 = m1 + funfactor[grandchild];
                        }
                    }
                }
            }
            int m0 = 0;
            for (int child : tree[vertex].children) 
            {
                if (child != parent) 
                {
                    m0 = m0 + funfactor[child];
                }
            }
            funfactor[vertex] = max(m1, m0);
        }
    }
}

int MaxWeightIndependentTreeSubset(Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
   vector<int> funfactor(tree.size());
   for (int i= 0; i < funfactor.size(); i++){
        funfactor[i]= INT_MAX;
    }
    dfs(tree, 0, -1, funfactor, 0);
    // You must decide what to return.
   int maxfun = INT_MIN;
    for (int i=0; i < funfactor.size(); i++)
    {
        if (funfactor[i] > maxfun)
        {
            maxfun = funfactor[i];
        }
    }
    return  maxfun;     
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Here begins the solution
    Graph tree = ReadTree();
    
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
