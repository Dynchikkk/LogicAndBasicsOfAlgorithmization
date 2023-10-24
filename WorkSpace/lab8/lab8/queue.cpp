#include <stdio.h>
#include <stdlib.h>
#include "list.h"

DataType* CreateQueue(int data)
{
	DataType* queue = CreateDataType(data);
	return queue;
}

DataType* Enqueue(int num, DataType* queue)
{
	if (IsDataTypeNull(queue) == 1)
	{
		queue = CreateQueue(num);
		return queue;
	}

	Add(num, queue);
	return queue;
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

int IsEmpty(DataType* queue)
{
	int* val = TryCheckElementAt(0, queue);

	if (val == NULL)
		return 1;
	else
		return 0;
}