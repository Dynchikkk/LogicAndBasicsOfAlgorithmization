#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

DataType* CreateStack(int data)
{
	DataType* stack = CreateDataType(data);
	return stack;
}

void Push(int num, DataType* stack)
{
	if (IsDataTypeNull(stack) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	Add(num, stack);
}

DataType* Pop(DataType* stack, int* val)
{
	if (IsDataTypeNull(stack) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	int lastElementPosition = *GetLength(stack) - 1;

	*val = *TryCheckElementAt(lastElementPosition, stack);
	stack = TryRemoveElementAt(lastElementPosition, stack);

	return stack;
}