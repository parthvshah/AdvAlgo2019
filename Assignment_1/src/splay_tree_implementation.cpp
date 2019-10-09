#include "../include/splay_tree.hpp"

using namespace std;

class node  
{  
    public: 
    int key;  
    node *left, *right;  
}; 

node* newNode(int key)  
{  
    node* Node = new node(); 
    Node->key = key;  
    Node->left = Node->right = NULL;  
    return (Node);  
}

int BSTSearch(node* root, int key)
{ 
    if(root == NULL) 
        return -1;
    if(key == root->key)
        return root->key;
    if(key < root->key) 
        return BSTSearch(root->left, key);
    if(key > root->key) 
        return BSTSearch(root->right, key);
}

node *BSTInsert(node* Node, int key) 
{ 
    if (Node == NULL)
        return newNode(key); 
  
    if (key < Node->key) 
        Node->left  = BSTInsert(Node->left, key); 
    else if (key > Node->key) 
        Node->right = BSTInsert(Node->right, key);    
  
    return Node; 
}

node *minValueNode(node *Node) 
{ 
    node *curr = Node; 
  
    while (curr && curr->left != NULL) 
        curr = curr->left; 
  
    return curr; 
} 

node* BSTDelete(node* root, int key, int *parentKey) 
{ 
    if (root == NULL)
        return root; 
  
    if (key < root->key)
    { 
        *parentKey = root->key;
        root->left = BSTDelete(root->left, key, parentKey); 
    }
  
    else if (key > root->key) 
    {
        *parentKey = root->key;
        root->right = BSTDelete(root->right, key, parentKey);
    } 
  
    else
    { 
        if (root->left == NULL) 
        { 
            struct node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            struct node *temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        struct node* temp = minValueNode(root->right); 
  
        root->key = temp->key; 
  
        root->right = BSTDelete(root->right, temp->key, parentKey); 
    } 
    return root; 
} 

node* rightRotate(node *x)  
{  
    node *y = x->left;  
    x->left = y->right;  
    y->right = x;  
    return y;  
}

node* leftRotate(node *x)  
{  
    node *y = x->right;  
    x->right = y->left;  
    y->left = x;  
    return y;  
}

node* splay(node *root, int key)  
{  
    if (root == NULL || root->key == key)  
        return root;  
  
    if (root->key > key)  
    {  
        if (root->left == NULL)
            return root;  
  
        if (root->left->key > key)  
        {  
            root->left->left = splay(root->left->left, key);  
            root = rightRotate(root);  
        }  
        else if (root->left->key < key)
        {  
            root->left->right = splay(root->left->right, key);  
  
            if (root->left->right != NULL)
            {  
                root->left = leftRotate(root->left);  
            }
        }  
  
        return(root->left == NULL)?root:rightRotate(root);  
    }  
    else 
    {  
        if (root->right == NULL)
            return root;  
  
        if (root->right->key > key)  
        {  
            root->right->left = splay(root->right->left, key);  
  
            if (root->right->left != NULL)  
            {
                root->right = rightRotate(root->right);  
            }
        }  
        else if (root->right->key < key)
        {  
            root->right->right = splay(root->right->right, key);  
            root = leftRotate(root);  
        }  
  
        return(root->right == NULL)?root:leftRotate(root);  
    }  
}  

class splay_tree_implementation : public splay_tree
{
    private:
    node *root;
    int num_nodes;

    public:
    splay_tree_implementation();
    virtual int get_num_nodes();
    virtual int find(int);
    virtual void insert(int);
    virtual void remove(int);
    virtual vector<int> post_order();
    virtual vector<int> in_order();
    virtual vector<int> pre_order();
    ~splay_tree_implementation();
};

// Constructor
splay_tree_implementation::splay_tree_implementation()
{
    root = NULL;
    num_nodes = 0;
}

int splay_tree_implementation::get_num_nodes()
{
    return num_nodes;
}

int splay_tree_implementation::find(int key)
{
    node *findNode = splay(root, key);
    root = findNode;
    if(findNode->key == key)
        return 1;
    else
        return 0;    
}

void splay_tree_implementation::insert(int key)
{   
    if(root != NULL)
    {
        if(BSTSearch(root, key) == key)
        {
            node *newRoot = splay(root, key);
            root = newRoot;
        }
        else
        {
            BSTInsert(root, key);
            node *newRoot = splay(root, key);
            root = newRoot;
            num_nodes++;
        }
    }
    else
    {
        root = BSTInsert(root, key);
        num_nodes++;
    }
}

void splay_tree_implementation::remove(int key)
{
    if(root != NULL)
    {
        if(BSTSearch(root, key) == key)
        {
            int parentKey;
            root = BSTDelete(root, key, &parentKey);
            node *newRoot = splay(root, parentKey);
            root = newRoot;
            num_nodes--;
        }
        else
        {
            node *newRoot = splay(root, key);
            root = newRoot;
        }
        
    }
    else
        return;
    
}

void pre_order_rec(node *root, vector<int> &res)  
{  
    if (root != NULL)  
    {  
        res.push_back(root->key);
        pre_order_rec(root->left, res);  
        pre_order_rec(root->right, res);  
    }  
}  

// Pre order wrapper
vector<int> splay_tree_implementation::pre_order()
{
    vector<int> res;  
    pre_order_rec(root, res);
    return(res);
}

void in_order_rec(node *root, vector<int> &res)  
{  
    if (root != NULL)  
    {  
        in_order_rec(root->left, res);  
        res.push_back(root->key);
        in_order_rec(root->right, res);
    }  
} 

// In order wrapper
vector<int> splay_tree_implementation::in_order()
{
    vector<int> res;  
    in_order_rec(root, res);
    return(res);
}

void post_order_rec(node *root, vector<int> &res)  
{  
    if (root != NULL)  
    {  
        pre_order_rec(root->left, res);  
        pre_order_rec(root->right, res);
        res.push_back(root->key);
    }  
} 

// Post order wrapper
vector<int> splay_tree_implementation::post_order()
{
    vector<int> res;  
    post_order_rec(root, res);
    return(res);
}

// Destructor
splay_tree_implementation::~splay_tree_implementation()
{

}
