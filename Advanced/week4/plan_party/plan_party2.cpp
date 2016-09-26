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
    finalSum.resize(vertices_count); 
    Graph tree(vertices_count);
    Sum funfactor(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
    {
        std::cin >> tree[i].weight;
        funfactor[i] = INT_MAX;

    }
    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int dfs(Graph &tree, int vertex, int parent) {
  /*   if (tree[vertex].visited == true)
        return 0;
    else 
        tree[vertex].visited = true;  */
   // tree[vertex].visited = true;
   
   // cout << " vertex ->number of children " << vertex << " " <<tree[vertex].children.size()  << endl;
    int total_children_sum = 0;
    if (tree.size() == 0)
    {
        // cout << "tree is empty\n"; 
        return 0;
    }
    
    if ((tree[vertex].children.size() == 0 ))
    {
        // cout << " only tree[" << vertex << "]= " << tree[vertex].weight << endl;
        return tree[vertex].weight;
    }
    
    // if tree has no children return weight of vertex
    if ((tree[vertex].children.size() == 1 )&& (vertex != 0)) // 0)
    {
        // cout << " only tree[" << vertex << "]= " << tree[vertex].weight << endl;
        return tree[vertex].weight;
    }
    // sum the weight of all the children
    for (int child : tree[vertex].children)
    {
        // cout << " parent " << parent <<  " vertex " << vertex << " child " << child << " weight " << tree[vertex].weight << endl; 
        if (child != parent) 
        {
            total_children_sum += dfs(tree, child, vertex);
            // cout << " sum child = " << total_children_sum << endl;
        }
        else
        {
           // total_children_sum += tree[vertex].weight;
            // cout << " vertex " << vertex << " child " << child << " curr weight " << tree[vertex].weight << endl;
            return tree[vertex].weight;
        }
        
    }
    
    // sum the weight of all the children's children
    int total_grandchildren_sum = 0; //tree[vertex].weight;
     for (int child : tree[vertex].children)
    {
        for (int grandchild : tree[child].children)
        {
            // cout << " child " << child <<  " grandchild " << grandchild <<  " weight " << tree[child].weight << endl; 
            if (grandchild != child) 
            {
                total_grandchildren_sum += dfs(tree, grandchild, child);
                // cout << " sum grandchildren = " << total_grandchildren_sum << endl;
            }
            else
            {
               // total_children_sum += tree[vertex].weight;
                // cout << " vertex " << vertex <<" grandchild " << grandchild << " curr weight " << tree[grandchild].weight << endl;
                return tree[child].weight;
                 
            }
        }
    }
    // cout << " this is the max " <<  max(total_children_sum, total_grandchildren_sum) << endl;
   // cout << "finalSum[" <<child << "] = " << finalSum[child] << endl;;
    // cout << " final sum " << totalSum << endl;
    // This is a template function for processing a tree using depth-first search.
    // Write your code here.
    // You may need to add more parameters to this function for child processing.
    return max(total_children_sum, total_grandchildren_sum);
}

int MaxWeightIndependentTreeSubset(Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    int total = dfs(tree, 0, -1);
    // You must decide what to return.
    return total;
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
