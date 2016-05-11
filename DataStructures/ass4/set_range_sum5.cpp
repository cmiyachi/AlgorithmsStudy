#include <cstdio>
#include <iostream>

using std::endl; 
using std::cout;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  int key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long sum;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
    if (v == NULL) return;
    if (v->parent == NULL) return;
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

void print_tree(Vertex* top)
{
    cout << "***";
    if (top != NULL)
    {
        cout << "key " << top->key << " ";
        cout << " ptr " << top << " "; 
        cout << " parent " << top->parent << " ";
        cout << " left ";
        print_tree(top->left);
        cout << " right ";
        print_tree(top->right);
    }
    else
        cout << " tree is null ";
    cout << endl;
}
// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, int key) {
  Vertex* v = root;
  Vertex* last = root;
  Vertex* next = NULL;
  while (v != NULL) {
    if (v->key >= key && (next == NULL || v->key < next->key)) {
      next = v;
    }
    last = v;
    if (v->key == key) {
      break;      
    }
    if (v->key < key) {
      v = v->right;
    } else {
      v = v->left;
    }
  }
  splay(root, last);
  return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
  right = find(root, key);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  split(root, x, left, right);
  if (right == NULL || right->key != x) {
    new_vertex = new Vertex(x, x, NULL, NULL, NULL);
  }
  root = merge(merge(left, new_vertex), right);
}

Vertex* LeftDescendant(Vertex* node)
{
    if (node->left == NULL)
        return node;
    else
        return LeftDescendant(node->left);
}

Vertex* RightAncestor(Vertex* node)
{
    if (node->key < (node->parent)->key)
        return node->parent;
    else
        return RightAncestor(node->parent);
}

Vertex* Next(Vertex* node)
{
    if (node->right != NULL)
        return LeftDescendant(node->right);
    else
        return RightAncestor(node);
}

void deleteNode(Vertex* delNode)
{
    if (root == NULL) return;
    if (delNode == NULL) return; 
    
    if (delNode->right == NULL)
    {
        // remove node
        Vertex* delParent = delNode->parent;
        Vertex* xLeft = delNode->left;
        if (delParent != NULL) // this is the root note
        {
            delParent->left = xLeft;
            xLeft->parent = delParent;
        }
        else // deleted node was the root
        {
            if (xLeft != NULL)
            {
                xLeft->parent = NULL;
                root = xLeft; 
            }
            else
            {
                // cout << " xleft is NULL! \n";
                root = NULL; 
            }
            
            // cout << "** parent null ** \n";
        }
       
    }
    else
    {
        Vertex* delParent = delNode->parent;
        Vertex* x = Next(delNode);
        Vertex* xRight = NULL;
        Vertex* xLeft = NULL;
        Vertex* xParent = NULL;
        // cout << "Next " << x << endl; 
        if (x == NULL)
        {
            delParent->right = x;
        }
        else 
        {
            xRight = x->right;
            xLeft = x->left;
            xParent = x->parent;
            //replace delNode by x-
            x->parent = delParent;
            if (delParent != NULL)
                delParent->left = x;
            // xRight->parent = xParent;
            if (xParent != NULL)
                xParent->left = xRight; 
            x->right = delNode->right;
            x->left = delNode->left;  // this is null
            update(x);
        }
    }
    
    delete(delNode); 
}

void erase(int x) {                   
  // Implement erase yourself
  // cout << " x to remove " << x << endl; 
  Vertex* temp = find(root, x);
  if (temp == NULL) return; 
  // Now I know that temp is at the root of the tree now 
  Vertex* temp_right = temp->right;
  Vertex* temp_left = temp->left; 
  if (temp_right != NULL) temp_right->parent = NULL;
  if (temp_left != NULL) temp_left->parent = NULL;
  delete(temp);
  root = merge(temp_left, temp_right);
  
 /*  if (temp != NULL)
  {
      splay(root, temp->parent);
      splay(root, temp);
      deleteNode(temp); 
     // update(root); 
      // delete the root and bring tree together
     // root = merge(root->left, root->right); 
      
   // cout << " root key "  << root->key << endl;
  }
  /* else
      cout << "not found to delete \n";  */ 
}

bool find(int x) {  
  // Implement find yourself
    Vertex* temp = NULL;
    temp = find(root, x);
    if (temp == NULL) return false; 
    if (temp->key == x)
        return true;
    else
        return false;
}

long long sum(int from, int to) {
    
  // Complete the implementation of sum
  long long ans = 0;
  Vertex* left = NULL;
  Vertex* middle1 = NULL;
  Vertex* right = NULL;
  split(root, from, left, middle1);
  split(middle1, to + 1, middle1, right);
  if (middle1 != NULL)
     ans = middle1->sum;
  else 
      ans = 0;
  // Complete the implementation of sum
  root = merge(left, merge(middle1,right)); 
  
  return ans;  
}

const int MODULO = 1000000001;

int main(){
  int n;
  scanf("%d", &n);
  int last_sum_result = 0;
  for (int i = 0; i < n; i++) {
   //  print_tree(root);
   // cout << " last sum " << last_sum_result << endl;
    char buffer[10];
    scanf("%s", buffer);
    char type = buffer[0];
    switch (type) {
      case '+' : {
        int x;
        scanf("%d", &x);
        insert((x + last_sum_result) % MODULO);
      } break;
      case '-' : {
        int x;
        scanf("%d", &x);
        erase((x + last_sum_result) % MODULO);
      } break;            
      case '?' : {
        int x;
        scanf("%d", &x);
        printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
      } break;
      case 's' : {
        int l, r;
        scanf("%d %d", &l, &r);
        long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
        printf("%lld\n", res);
        last_sum_result = int(res % MODULO);
      }
    }
  }
  return 0;
}
