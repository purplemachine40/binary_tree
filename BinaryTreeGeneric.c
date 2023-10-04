#include <stdio.h>
#include <stdlib.h>
#include "BinaryTreeGeneric.h"

struct TreeNode *CreateNode(const void *data, size_t dataSize)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL)
    {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL)
    {
        // Handle memory allocation error
        free(newNode);
        exit(EXIT_FAILURE);
    }
    memcpy(newNode->data, data, dataSize);
    newNode->dataSize = dataSize;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode *InsertNode(struct TreeNode *root, const void *data, size_t dataSize, int (*compare)(const void *, const void *))
{
    if (root == NULL)
    {
        return CreateNode(data, dataSize);
    }

    // Compare data values to decide the subtree
    if (compare(data, root->data) < 0)
    {
        root->left = InsertNode(root->left, data, dataSize, compare);
    }
    else if (compare(data, root->data) > 0)
    {
        root->right = InsertNode(root->right, data, dataSize, compare);
    }

    return root;
}

void InOrderTraversal(struct TreeNode *root, void (*print)(const void *))
{
    if (root == NULL)
    {
        return;
    }

    InOrderTraversal(root->left, print);
    print(root->data);
    InOrderTraversal(root->right, print);
}

void FreeTree(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    FreeTree(root->left);
    FreeTree(root->right);
    free(root->data);
    free(root);
}
