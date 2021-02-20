#include <stdio.h>
#include "stdlib.h"
#include "BinarySearchTree.h"


 BinarySearchTree *createBinaryTree() {
    BinarySearchTree *bst = (BinarySearchTree*) (malloc(sizeof(BinarySearchTree)));
    bst->root = NULL;
    bst->size = 0;
}

Node *newNode(int value) {
    Node *newnode = NULL;
    newnode = (Node*)(malloc(sizeof(Node)));
    if (newnode) {
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
    }
    else return NULL;
}

 void insert(BinarySearchTree *bst , int value) {   
    if(bst->root == NULL) {
        bst->root = newNode(value);
        bst->size++;
        return;
    }
    Node *current = bst->root;
    Node *prev = NULL;
    while(current) {
        prev = current;
        if (current->data < value) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    if (prev->data < value) prev->right = newNode(value);
    else prev->left = newNode(value);
    bst->size ++;
}

Boolean isaLeaf(Node* current) {
        return (current->right == NULL && current->left == NULL);
}
Node* findMin(Node *current) {
    while (current->left) {
        current = current->left;
    }
    return current;
}

Node *delete(BinarySearchTree *bst , Node *current , int value) {
  
    if(!current) return current;
    if (current->data < value) current->right = delete(bst,current->right,value);
    else if (current->data > value) current->left = delete(bst,current->left,value);
    
    else {
    if(isaLeaf(current)) {
        free(current);
        current = NULL;
        bst->size--;
        return current;
    }
    else if (current->right == NULL || current->left == NULL) {
    
        if(current->right == NULL) {
          Node *leftChild = current->left;
          free(current);
          current = NULL;
          bst->size--;
          return leftChild;        
        }
        else {
          Node *rightChild = current->right;
          free(current);
          current = NULL;
          bst->size--;
          return rightChild;
        }
    }
        Node *minChild = findMin(current->right);
        int minData = minChild->data;
        current->data = minData;
        current->right = delete(bst,current->right,minData);
    }

        return current;
}

void postOrder(Node *current) {
    if (!current) return;
    postOrder(current->left);
    postOrder(current->right);
    free(current);

}
void treeFree(BinarySearchTree *bst) {
    postOrder(bst->root);
    free(bst);
}
 

  