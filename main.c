#include <stdio.h>
#include <stdlib.h>

#include "BinaryTreeGeneric.h"
#include "SensorData.h"
#include "Utils.h"

#define NUM_DATA_POINTS 100
#define FIND_IDX (int)(NUM_DATA_POINTS / 2)

static struct TS_SENSOR_DATA sensorData[NUM_DATA_POINTS];

static int CompareTimestamp(const void *a, const void *b);
static void PrintSensorData(const void *pData);

int main()
{
   struct TreeNode *root = NULL;
   struct TreeNode *foundRoot = NULL;

   InitRandomNumberGenerator();
   GenerateRandomSensorData(&sensorData[0], NUM_DATA_POINTS);

   // Insert nodes into the binary search tree

   for (int i = 0; i < NUM_DATA_POINTS; i++)
   {
      root = InsertNode(root, (void *)&sensorData[i], sizeof(struct TS_SENSOR_DATA), CompareTimestamp);
   }

   // Print in-order traversal of the binary search tree
   printf("In-order traversal of the binary tree\n");
   InOrderTraversal(root, PrintSensorData);
   printf("\n");

   // Find one of the timestamps.
   foundRoot = FindNode(root, (void *)&sensorData[FIND_IDX], sizeof(struct TS_SENSOR_DATA), CompareTimestamp);
   if (foundRoot != NULL)
   {
       struct TS_SENSOR_DATA* pFound = (struct TS_SENSOR_DATA*)foundRoot->data;
       printf("Timestamp searched for: %d\n", sensorData[FIND_IDX].epochTimestamp);
       printf("Timestamp found: %d", pFound->epochTimestamp);
   }
   else
   {
       printf("Node not found!");
   }


   // Free memory by deleting nodes
   FreeTree(root);
   return 0;
}

int CompareTimestamp(const void *a, const void *b)
{
   struct TS_SENSOR_DATA *pA = (struct TS_SENSOR_DATA *)a;
   struct TS_SENSOR_DATA *pB = (struct TS_SENSOR_DATA *)b;
   return (pA->epochTimestamp - pB->epochTimestamp);
}

void PrintSensorData(const void *pData)
{
   struct TS_SENSOR_DATA *pSensorData = (struct TS_SENSOR_DATA *)pData;
   printf("Timestamp: %d\n", pSensorData->epochTimestamp);
   printf("Temperature: %.2f\n\n", pSensorData->temperature);
}
