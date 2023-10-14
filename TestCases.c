#include <stdio.h>
#include "BinaryTreeGeneric.h"

#define SIZE_TEST_ARRAY 7
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"

static int nodeCnt = 0;

int CompareInt(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void PrintInt(const void *data)
{
    // printf("%d ", *(int *)data);
    nodeCnt++;
}

void PrintColored(const char *text, const char *color)
{
    printf("%s%s\x1b[0m", color, text); // \x1b[0m resets color to default
}

void PrintTestPassed(void)
{
    PrintColored("Pass", GREEN);
}

void PrintTestFailed(void)
{
    PrintColored("Failed", RED);
}

void PrintPassFail(const char *text, unsigned int isPass)
{
    printf("%s: ", text);
    isPass ? PrintTestPassed() : PrintTestFailed();
    printf("\n");
}

void TestBinaryTree(void)
{
    struct TreeNode *root = NULL;
    int testOk;

    printf("******** BEGIN TEST ********\n");
    int values[SIZE_TEST_ARRAY] = {5, 3, 7, 2, 4, 6, 8};
    size_t dataSize = sizeof(int);
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        root = InsertNode(root, &values[i], dataSize, CompareInt);
    }

    // Test case: Check if all values are in the tree
    testOk = 1;
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        struct TreeNode *foundNode = FindNode(root, &values[i], dataSize, CompareInt);
        if (foundNode == NULL)
        {
            testOk = 0;
        }
    }

    PrintPassFail("Insert Node test", testOk);

    // Test case: FindNode() with an existing integer
    int searchValue = 4;
    struct TreeNode *foundNode = FindNode(root, &searchValue, dataSize, CompareInt);
    PrintPassFail("Find Existing Node test", (foundNode != NULL) && (*(int *)foundNode->data == searchValue));

    // Test case: FindNode() with a non-existing integer
    int nonExistingValue = 9;
    foundNode = FindNode(root, &nonExistingValue, dataSize, CompareInt);
    PrintPassFail("Find Non-Existing Node test", (foundNode == NULL));

    // Test case: DeleteNode() with an existing integer (child node)
    int deleteValue = 7;
    nodeCnt = 0;
    root = DeleteNode(root, &deleteValue, dataSize, CompareInt);
    InOrderTraversal(root, PrintInt);
    foundNode = FindNode(root, &deleteValue, dataSize, CompareInt);
    PrintPassFail("Delete Child Node test", ((foundNode == NULL) && (nodeCnt == (SIZE_TEST_ARRAY - 1))));

    // Test case: Deleting the root node
    deleteValue = 5;
    nodeCnt = 0;
    root = DeleteNode(root, &deleteValue, dataSize, CompareInt);
    InOrderTraversal(root, PrintInt);
    foundNode = FindNode(root, &deleteValue, dataSize, CompareInt);
    PrintPassFail("Delete Root Node test", ((foundNode == NULL) && (nodeCnt == (SIZE_TEST_ARRAY - 2))));

    // Test case: DeleteNode() with a non-existing integer
    int nonExistingDeleteValue = 9;
    nodeCnt = 0;
    root = DeleteNode(root, &nonExistingDeleteValue, dataSize, CompareInt);
    InOrderTraversal(root, PrintInt);
    PrintPassFail("Delete Non-Existing Node test", (nodeCnt == (SIZE_TEST_ARRAY - 2)));

    // Free memory
    FreeTree(root);
    printf("******** END TEST ********\n\n");
}
