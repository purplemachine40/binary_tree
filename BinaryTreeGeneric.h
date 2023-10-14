#pragma once

struct TreeNode
{
    void *data;
    size_t dataSize; // Size of the data
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *CreateNode(const void *data, size_t dataSize);
struct TreeNode *InsertNode(struct TreeNode *root, const void *data, size_t dataSize,
                            int (*compare)(const void *, const void *));
void InOrderTraversal(struct TreeNode *root, void (*print)(const void *));
struct TreeNode *FindNode(struct TreeNode *root, const void *data, size_t dataSize,
                          int (*compare)(const void *, const void *));
struct TreeNode *DeleteNode(struct TreeNode *root, const void *data, size_t dataSize,
                            int (*compare)(const void *, const void *));
void FreeTree(struct TreeNode *root);
