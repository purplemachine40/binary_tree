#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTreeGeneric.h"

static struct TreeNode *DeleteRootNode(struct TreeNode *root, int (*compare)(const void *, const void *));
static struct TreeNode *DeleteChildNode(struct TreeNode *root, struct TreeNode *node, int (*compare)(const void *, const void *));
static void RemoveNodeLink(struct TreeNode *root, struct TreeNode *pNodeAdrs);
static struct TreeNode *FindLinkFreeNode(struct TreeNode *node);
static struct TreeNode *InsertExistingNode(struct TreeNode *root, struct TreeNode *node,
                                           int (*compare)(const void *, const void *));

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

struct TreeNode *FindNode(struct TreeNode *root, const void *data, size_t dataSize, int (*compare)(const void *, const void *))
{
    int compareResult;

    while (root != NULL)
    {
        compareResult = compare(data, root->data);
        if (compareResult == 0)
        {
            return root;
        }
        else
        {
            root = (compareResult < 0) ? root->left : root->right;
        }
    }

    return root;
}

struct TreeNode *DeleteNode(struct TreeNode *root, const void *data, size_t dataSize, int (*compare)(const void *, const void *))
{
    struct TreeNode *node = FindNode(root, data, dataSize, compare);

    if ((root == NULL) || (node == NULL))
    {
        return root;
    }

    if (node == root)
    {
        return DeleteRootNode(root, compare);
    }

    return DeleteChildNode(root, node, compare);
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

static struct TreeNode *DeleteRootNode(struct TreeNode *root, int (*compare)(const void *, const void *))
{
    struct TreeNode *linkFreeNode;
    struct TreeNode *nodeLeft;
    struct TreeNode *nodeRight;

    nodeLeft = root->left;
    nodeRight = root->right;
    root->left = NULL;
    root->right = NULL;
    FreeTree(root);

    if ((nodeLeft == NULL) && (nodeRight == NULL))
    {
        return NULL;
    }
    else if (nodeLeft == NULL)
    {
        return nodeRight;
    }
    else if (nodeRight == NULL)
    {
        return nodeLeft;
    }
    else
    {
        while ((linkFreeNode = FindLinkFreeNode(nodeLeft)) != nodeLeft)
        {
            InsertExistingNode(nodeRight, linkFreeNode, compare);
            RemoveNodeLink(nodeLeft, linkFreeNode);
        }

        InsertExistingNode(nodeRight, nodeLeft, compare);
        return nodeRight;
    }
}

static struct TreeNode *DeleteChildNode(struct TreeNode *root, struct TreeNode* node, int (*compare)(const void *, const void *))
{
    struct TreeNode *linkFreeNode;

    if ((root == NULL) || (node == NULL))
    {
        return root;
    }

    RemoveNodeLink(root, node);

    // Insert anything under node into root.

    while ((linkFreeNode = FindLinkFreeNode(node)) != node)
    {
        InsertExistingNode(root, linkFreeNode, compare);
        RemoveNodeLink(node, linkFreeNode);
    }

    // Nothing is left under node, so ok to delete it.

    FreeTree(node);
    return root;
}

static void RemoveNodeLink(struct TreeNode *root, struct TreeNode* nodeToRemove)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == nodeToRemove)
    {
        root->left = NULL;
        return;
    }
    else if (root->right == nodeToRemove)
    {
        root->right = NULL;
        return;
    }
    else
    {
        RemoveNodeLink(root->left, nodeToRemove);
        RemoveNodeLink(root->right, nodeToRemove);
    }
}

static struct TreeNode *FindLinkFreeNode(struct TreeNode *node)
{
    while (node->left || node->right)
    {
        node = node->left ? node->left : node->right;
    }

    return node;
}

static struct TreeNode *InsertExistingNode(struct TreeNode *root, struct TreeNode *node, int (*compare)(const void *, const void *))
{
    if (root == NULL)
    {        
        return node;
    }

    // Compare data values to decide the subtree
    if (compare(node->data, root->data) < 0)
    {
        root->left = InsertExistingNode(root->left, node, compare);
    }
    else if (compare(node->data, root->data) > 0)
    {
        root->right = InsertExistingNode(root->right, node, compare);
    }

    return root;
}
