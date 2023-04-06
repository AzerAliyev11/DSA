#include <iostream>
#include<algorithm>
using namespace std;

class TreeNode
{
  public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    
    TreeNode(int value, TreeNode *prev):val(value),left(NULL),right(NULL),parent(prev){}
};

// void Insert(TreeNode *&tree, int val)
// {
//     if (tree == NULL)
//     {
//         tree = new TreeNode(val);
//         return;
//     }
    
//     if(val < tree->val)
//     {
//         Insert(tree->left, val);
//     }
//     else
//     {
//         Insert(tree->right, val);
//     }
// }

TreeNode *InsertwithParent(TreeNode *&tree, int val)
{
    if(tree == NULL)
    {
        tree = new TreeNode(val, NULL);
        return tree;
    }
    
    if(val < tree->val)
    {
        TreeNode *leftChild = InsertwithParent(tree->left, val);
        leftChild->parent = tree;
    }
    else
    {
        TreeNode *rightChild = InsertwithParent(tree->right, val);
        rightChild->parent = tree;
    }
    
    return tree;
}

void InOrder(TreeNode *tree)
{
    if(tree != NULL)
    {
        InOrder(tree->left);
        cout<<tree->val<<" ";
        InOrder(tree->right);
    }
}

TreeNode *FindElement(TreeNode *tree, int val)
{
    if(tree == NULL) 
    {
        return NULL;
    }
    
    if(tree->val == val)
    {
        return tree;
    }
    
    if(val < tree->val)
    {
        return FindElement(tree->left, val);
    }
    else
    {
        return FindElement(tree->right, val);
    }
}

TreeNode *Minimum(TreeNode *tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    while(tree->left != NULL)
    {
        tree = tree->left;
    }
    return tree;
}

TreeNode *Maximum(TreeNode *tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    while(tree->right != NULL)
    {
        tree = tree->right;
    }
    return tree;
}

TreeNode *NextElement(TreeNode *tree)
{
    if(tree->right != NULL)
    {
        return Minimum(tree->right);
    }
    else
    {
        TreeNode *prev = tree->parent;
        
        while(prev != NULL && tree == prev->right)
        {
            //cout<<prev->val<<" ";
            tree = prev;
            prev = prev->parent;
        }
        
        return prev;
    }
}

TreeNode *PrevElement(TreeNode *tree)
{
    if(tree->left != NULL)
    {
        return Maximum(tree->left);
    }
    else
    {
        TreeNode *prev = tree->parent;
        
        while(prev != NULL && tree == prev->left)
        {
            tree = prev;
            prev = prev->parent;
        }
        
        return prev;
    }
}

int MinDepth(TreeNode *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    if(tree->left == NULL)
    {
        return MinDepth(tree->right)+1;
    }
    if(tree->right == NULL)
    {
        return MinDepth(tree->left)+1;
    }
    
    int left = MinDepth(tree->left);
    int right = MinDepth(tree->right);
    return min(left, right) + 1;
}

int MaxDepth(TreeNode *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    int left = MaxDepth(tree->left);
    int right = MaxDepth(tree->right);
    return max(left, right) + 1;
}

int SumLeft(TreeNode *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    if(tree->left != NULL && tree->left->left == NULL && tree->left->right == NULL)
    {
        return tree->left->val + SumLeft(tree->right);
    }
    return SumLeft(tree->left) + SumLeft(tree->right);
}

int Height(TreeNode *tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    int left = Height(tree->left);
    int right = Height(tree->right);
    
    if(left == -1 || right == -1 || abs(left-right) > 1)
    {
        return -1;
    }
    
    return max(left, right) + 1;
}

bool IsBalanced(TreeNode *tree)
{
    return Height(tree) != -1;
}

int main()
{
    TreeNode *tree = new TreeNode(11, NULL);
    InsertwithParent(tree, 13);
    InsertwithParent(tree, 6);
    InsertwithParent(tree, 4);
    InsertwithParent(tree, 7);
    InsertwithParent(tree, 2);
    InOrder(tree);
    cout<<endl;
    
    if(FindElement(tree, 12) == NULL)
    {
        cout<<"No such element"<<endl;
    }
    else
    {
        cout<<"element exists"<<endl;
    }
    
    TreeNode *min = Minimum(tree);
    if(min != NULL)
    {
        cout<<"Minimum: "<<min->val<<endl;
    }
    else
    {
        cout<<"Tree is empty"<<endl;
    }
    
    TreeNode *max = Maximum(tree);
    if(max != NULL)
    {
        cout<<"Maximum: "<<max->val<<endl;
    }
    else
    {
        cout<<"Tree is empty"<<endl;
    }
    
    cout<<NextElement(FindElement(tree, 11))->val<<endl;
    cout<<PrevElement(FindElement(tree, 11))->val<<endl;
    
    cout<<MinDepth(tree)<<endl;
    cout<<MaxDepth(tree)<<endl;
    
    cout<<SumLeft(tree)<<endl;
    
    if(IsBalanced(tree))
    {
        cout<<"Balanced"<<endl;
    }
    else
    {
        cout<<"Unbalanced"<<endl;
    }
}