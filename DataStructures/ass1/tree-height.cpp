#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int height(std::vector<int> tree);

class TreeHeight {
  int n;             
  std::vector<int> parent;
  std::vector<int> length_set; 

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
    length_set.resize(n);

    for (int i = 0; i < n; i++)
    {
      std::cin >> parent[i];
      length_set[i] = 0; // 0 indicates no length for that vertex has been set
    }
  
  }

  int compute_height() {
    // Replace this code with a faster implementation
    int maxHeight = 0;
    for (int vertex = 0; vertex < n; vertex++) {
      int height = 0;
     // std::cout <<  " vertex above " << vertex  <<  std::endl;
      for (int i = vertex; i != -1; i = parent[i])
      {
        if (length_set[i] != 0) // this has been set so use this instead
        {
            height = height + length_set[i]; 
          //  std::cout << " i " << i << " vertex " << vertex  << " p " << parent[i] << std::endl;
           // std::cout << "hieght break  " << height << std::endl; 
            break;
        }
        else
        {
            height++;
          //  std::cout << " i " << i << " vertex " << vertex  << " p " << parent[i] << std::endl;
           // std::cout << "h " << height << std::endl; 
        }
      } 
      maxHeight = std::max(maxHeight, height);
      length_set[vertex] = height; 
    }
//    maxHeight = height(parent);
    return maxHeight;
  }
};

/* int height(std::vector<int> tree)
{
    unsigned int h = 0;
    
    for (int i = 0; i < tree.size(); i++)
    {
        h = std::max(h, height(tree[i])); 
    }
    
    return h+1;
} */
/* 
int hight(TreeNode* node) {
    vector<TreeNode*>& children = node.getChildren();
    unsigned int h = 0;
    for(int i = 0; i < children.size(); i++) {
        h = std::max(h, hight(children[i]));
    }
    return h + 1;
} */
int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
