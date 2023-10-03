#pragma once

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int value);
struct TreeNode* insertNode(struct TreeNode* root, int value);
void inOrderTraversal(struct TreeNode* root);
void freeTree(struct TreeNode* root);