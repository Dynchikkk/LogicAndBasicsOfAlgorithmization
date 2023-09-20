#include <stdio.h>
#include <stdlib.h>
#include "prior_queue.h"

DataType* CreatePrQueue(int data)
{
	DataType* prQueue = CreateDataType(data);
	return prQueue;
}

void EnqueuePr(int num, DataType* prQueue)
{
	if (IsDataTypeNull(prQueue) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	Add(num, prQueue);
}

DataType* DequeuePr(DataType* prQueue, int *val)
{
	if (IsDataTypeNull(prQueue) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	int size = *GetLength(prQueue);

	int comparer = prQueue->value;
	int maxPriorityElementPos = 0;
	int maxPriorityElementValue = comparer;

	for (int i = 0; i < size; i++)
	{
		int* tmp = TryCheckElementAt(i, prQueue);
		if (*tmp > comparer)
		{
			maxPriorityElementPos = i;
			maxPriorityElementValue = *tmp;
			comparer = maxPriorityElementValue;
		}
	}

	prQueue = TryRemoveElementAt(maxPriorityElementPos, prQueue);
	*val = maxPriorityElementValue;

	return prQueue;
}