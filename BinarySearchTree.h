#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

typedef enum {True = 1,False = 0} Boolean;
typedef struct Node {
    int data;
    struct Node *left , *right;
} Node;

typedef struct BinarySearchTree
{   
    size_t size;
    Node *root;

} BinarySearchTree;

BinarySearchTree *createBinaryTree();
Node *newNode(int);
void insert(BinarySearchTree*,int);
Node* findMin(Node *);
Boolean isaLeaf(Node* current);
Node *delete(BinarySearchTree *, Node*, int);
void print2DUtil(struct Node *root, int space);
void print2D(struct Node *root);
void treeFree(BinarySearchTree *bst);
void postOrder(Node *current);
#endif // BINARY_SEARCH_TREE_H
