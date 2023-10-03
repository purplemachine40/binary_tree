#include <stdio.h>
#include <stdlib.h>

#include "BinaryTree.h"
#include "Utils.h"

static struct TreeNode* InsertSimpleTree(struct TreeNode* root);

int main() {
    struct TreeNode* root = NULL;

    //Insert nodes into the binary search tree
    //root = InsertSimpleTree(root);

    InitRandomNumberGenerator();
    for(int i = 0; i < 10; i++) {
       root = insertNode(root, GenerateRandomNumber(0, 1000));
    }
    
    // Print in-order traversal of the binary search tree
    printf("In-order traversal of the binary tree: ");
    inOrderTraversal(root);
    printf("\n");

    // Free memory by deleting nodes
    freeTree(root);

    return 0;
}


static struct TreeNode* InsertSimpleTree(struct TreeNode* root) {
   root = insertNode(root, 50);
   insertNode(root, 30);
   insertNode(root, 70);
   insertNode(root, 20);
   insertNode(root, 40);
   return root;
}