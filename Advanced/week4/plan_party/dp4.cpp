/* Dynamic programming based program for Largest Independent Set problem */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sys/resource.h>
#include <algorithm>

using namespace std; 


struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}
 
/* A binary tree node has data, pointer to left child and a pointer to 
   right child */
struct node
{
    int data;
    int liss;
    int liss_max_data;
    struct node *children;
    int no_children; 
};


// A memoization function returns size of the largest independent set in
//  a given binary tree
int LISS_DATA(Graph root, vertex)
{
     
    
    if (root.size() == 0)
    {
        cout << "root is null\n"; 
        return 0;
    }
 cout << "entering data " << root[0].weight << endl;
   /* if (root->liss)
    {
        return root->liss_data;
        cout << " *** weight " << root->liss_data << " " << root-> data << endl; 
        
    }  */
 
   // if (root->left == NULL && root->right == NULL)
    if (root[0].children.size() == 0)
    {
        return (root[0].weight);
        cout << " only root " << root[0].weight << endl; 
    }
 
    // Calculate size excluding the current node
    int liss_data_excl = LISS_DATA(root->children)
    cout << " at node weight " << root->data << " sum excl " << liss_data_excl << endl; 
 
    // Calculate size including the current node
    int liss_data_incl = root->data; //root->liss_data;
    for (i = 0; i < root->no_children; i++)
    {
        
        liss_data_incl += LISS_DATA(root->children[i]); 
        cout << " at node weight " << root->data << " sum incl TOTAL  " << liss_data_incl << endl; 
    }
 
    // Maximum of two sizes is LISS, store it for future uses.
    int liss_data_final = max(liss_data_incl, liss_data_excl);
    cout << " max " << liss_data_final << endl; 
    root->liss_max_data = liss_data_final;
 
    return liss_data_final;
}

 
// A utility function to create a node
struct node* newNode(int data)
{
    struct node* temp = (struct node *) malloc( sizeof(struct node) );
    temp->data = data;
    temp->children = NULL;
    temp->liss = 0;
    return temp;
}
 
// Driver program to test above functions
int main()
{
    // Let us construct the tree given in the above diagram
  /*   struct node *root         = newNode(20);
    root->left                = newNode(8);
    root->left->left          = newNode(4);
    root->left->right         = newNode(12);
    root->left->right->left   = newNode(10);
    root->left->right->right  = newNode(14);
    root->right               = newNode(22);
    root->right->right        = newNode(25); */
  /*   
      struct node *root         = newNode(1);
    root->left                = newNode(5);
    root->left->left          = newNode(3);
    root->left->right         = newNode(7);
    root->left->right->left   = newNode(5);

 
    printf ("%d ", LISS_DATA(root)); */
    
   /*  struct node *root2 = newNode(1000);
     printf ("Weight of the Largest Independent Set is %d ", LISS_DATA(root2));
     
    struct node *root3         = newNode(1);
    root3->left                = newNode(2);
   

 
    printf ("Weight of the Largest Independent Set is %d ", LISS_DATA(root3)); */
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
    int weight = LISS_DATA(tree);
    std::cout << weight << std::endl;
    return 0;
 
    return 0;
}