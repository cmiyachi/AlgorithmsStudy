/* Dynamic programming based program for Largest Independent Set problem */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std; 
 
// A utility function to find max of two integers
int max(int x, int y) { return (x > y)? x: y; }
 
/* A binary tree node has data, pointer to left child and a pointer to 
   right child */
struct node
{
    int data;
    int liss;
    int liss_max_data;
    struct node *left, *right;
};


// A memoization function returns size of the largest independent set in
//  a given binary tree
int LISS_DATA(struct node *root)
{
     
    
    if (root == NULL)
    {
        cout << "root is null\n"; 
        return 0;
    }
 cout << "entering data " << root->data << endl;
   /* if (root->liss)
    {
        return root->liss_data;
        cout << " *** weight " << root->liss_data << " " << root-> data << endl; 
        
    }  */
 
    if (root->left == NULL && root->right == NULL)
    {
        return (root->data);
        cout << " only root " << root->data << endl; 
    }
 
    // Calculate size excluding the current node
    int liss_data_excl = LISS_DATA(root->left) + LISS_DATA(root->right);
    cout << " at node weight " << root->data << " sum excl " << liss_data_excl << endl; 
 
    // Calculate size including the current node
    int liss_data_incl = root->data; //root->liss_data;
    if (root->left)
    {
        liss_data_incl += LISS_DATA(root->left->left) + LISS_DATA(root->left->right);
        cout << " at node weight " << root->data << " sum incl LEFT  " << liss_data_incl << endl; 
    }
        
    if (root->right)
    {
        liss_data_incl += LISS_DATA(root->right->left) + LISS_DATA(root->right->right);
        cout << " at node weight " << root->data << " sum incl RIGHT  " << liss_data_incl << endl; 
    }
 
    // Maximum of two sizes is LISS, store it for future uses.
    int liss_data_final = max(liss_data_incl, liss_data_excl);
    cout << " max " << liss_data_final << endl; 
    root->liss_max_data = liss_data_final;
 
    return liss_data_final;
}

// A memoization function returns size of the largest independent set in
//  a given binary tree
int LISS(struct node *root)
{
 
    
    if (root == NULL)
        return 0;
 
    if (root->liss)
    {
        return root->liss;
      
        
    }
 
    if (root->left == NULL && root->right == NULL)
    {
        return (root->liss = 1);
       
    }
 
    // Calculate size excluding the current node
    int liss_excl = LISS(root->left) + LISS(root->right);
 
    // Calculate size including the current node
    int liss_incl = 1;
    if (root->left)
    {
        liss_incl += LISS(root->left->left) + LISS(root->left->right);
    }
        
    if (root->right)
    {
        liss_incl += LISS(root->right->left) + LISS(root->right->right);
    }
 
    // Maximum of two sizes is LISS, store it for future uses.
    root->liss = max(liss_incl, liss_excl);
 
    return root->liss;
}
 
// A utility function to create a node
struct node* newNode(int data)
{
    struct node* temp = (struct node *) malloc( sizeof(struct node) );
    temp->data = data;
    temp->left = temp->right = NULL;
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
    
      struct node *root         = newNode(1);
    root->left                = newNode(5);
    root->left->left          = newNode(3);
    root->left->right         = newNode(7);
    root->left->right->left   = newNode(5);

 
    printf ("%d ", LISS_DATA(root));
    
   /*  struct node *root2 = newNode(1000);
     printf ("Weight of the Largest Independent Set is %d ", LISS_DATA(root2));
     
    struct node *root3         = newNode(1);
    root3->left                = newNode(2);
   

 
    printf ("Weight of the Largest Independent Set is %d ", LISS_DATA(root3)); */
    
 
    return 0;
}