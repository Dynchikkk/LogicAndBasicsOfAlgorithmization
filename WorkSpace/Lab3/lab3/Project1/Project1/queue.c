#include <stdio.h>
#include <stdlib.h>
#include "prior_queue.h"

DataType* CreateQueue(int data)
{
	DataType* queue = CreateDataType(data);
	return queue;
}

void Enqueue(int num, DataType* queue)
{
	if (IsDataTypeNull(queue) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	Add(num, queue);
}

DataType* Dequeue(DataType* queue, int* val)
{
	if (IsDataTypeNull(queue) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	*val = *TryCheckElementAt(0, queue);
	queue = TryRemoveElementAt(0, queue);
	return queue;
}