#include <stdio.h>
#include <stdlib.h>

#include "BinaryTreeGeneric.h"
#include "SensorData.h"
#include "SensorTree.h"
#include "Utils.h"

#define NUM_DATA_POINTS 10
#define FIND_IDX (int)(NUM_DATA_POINTS / 2)

struct TreeNode *root = NULL;
static struct TS_SENSOR_DATA sensorData[NUM_DATA_POINTS];

static void InsertSensorDataIntoTree(void);
static void FindAndPrintTimestamp(struct TS_SENSOR_DATA *pSensorData);
static int CompareTimestamp(const void *a, const void *b);
static void PrintNode(struct TreeNode *node);
static void PrintSensorData(const void *pData);

void TestSensorTree(void)
{
    struct TreeNode *foundNode = NULL;

    printf("******** BEGIN SENSOR DATA TEST ********\n");

    InitRandomNumberGenerator();
    GenerateRandomSensorData(&sensorData[0], NUM_DATA_POINTS);
    InsertSensorDataIntoTree();

    // Print in-order traversal of the binary search tree
    printf("****** Ordered Sensor Data ******\n\n");
    InOrderTraversal(root, PrintSensorData);
    printf("*********************************\n\n");

    // Find one of the timestamps.
    FindAndPrintTimestamp(&sensorData[FIND_IDX]);
    // Corrupt the timestamp and try again to test the "not found" case.
    // printf("Corrupted timestamp test case\n\n");
    // sensorData[FIND_IDX].epochTimestamp = 9;
    // FindAndPrintTimestamp(&sensorData[FIND_IDX]);

    printf("********** Delete Node **********\n\n");
    printf("Deleting timestamp: %d\n", sensorData[FIND_IDX].epochTimestamp);
    DeleteNode(root, (void *)&sensorData[FIND_IDX], sizeof(struct TS_SENSOR_DATA), CompareTimestamp);
    printf("Tree after deletion.\n\n");
    InOrderTraversal(root, PrintSensorData);
    printf("*********************************\n\n");

    // Free memory by deleting nodes
    FreeTree(root);

    printf("******** END SENSOR DATA TEST ********\n");
}

static void InsertSensorDataIntoTree(void)
{
    for (int i = 0; i < NUM_DATA_POINTS; i++)
    {
        root = InsertNode(root, (void *)&sensorData[i], sizeof(struct TS_SENSOR_DATA), CompareTimestamp);
    }
}

static void FindAndPrintTimestamp(struct TS_SENSOR_DATA *pSensorData)
{
    struct TreeNode *foundRoot = NULL;
    printf("Searching for this node:\n");
    PrintSensorData((void *)pSensorData);
    foundRoot = FindNode(root, (void *)pSensorData, sizeof(struct TS_SENSOR_DATA), CompareTimestamp);
    printf("Found this node:\n");
    PrintNode(foundRoot);
}

int CompareTimestamp(const void *a, const void *b)
{
    struct TS_SENSOR_DATA *pA = (struct TS_SENSOR_DATA *)a;
    struct TS_SENSOR_DATA *pB = (struct TS_SENSOR_DATA *)b;
    return (pA->epochTimestamp - pB->epochTimestamp);
}

static void PrintNode(struct TreeNode *node)
{
    if (node != NULL)
    {
        PrintSensorData(node->data);
    }
    else
    {
        printf("Node does not exist!\n");
    }
}

void PrintSensorData(const void *pData)
{
    struct TS_SENSOR_DATA *pSensorData = (struct TS_SENSOR_DATA *)pData;
    printf("Timestamp: %d\n", pSensorData->epochTimestamp);
    printf("Temperature: %.2f\n\n", pSensorData->temperature);
}