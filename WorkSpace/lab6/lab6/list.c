#include <stdio.h>
#include <stdlib.h>
#include "list.h"

DataType* CreateElement(int data)
{
	DataType* tmp = (DataType*)malloc(sizeof(DataType));

	if (tmp == NULL)
	{
		printf("ERROR: No memory");
		return NULL;
	}

	tmp->value = data;
	tmp->next = NULL;

	return tmp;
}

int IsDataTypeNull(DataType* head)
{
	if (head == NULL)
		return 1;
	else
		return 0;
}

DataType* CreateDataType(int data)
{
	DataType* tmp = CreateElement(data);
	return tmp;
}

void Add(int data, DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return;
	}

	DataType* tmp = CreateElement(data);
	if (tmp == NULL)
		return;

	DataType* l = head;

	while (l->next != NULL)
	{
		l = l->next;
	}

	l->next = tmp;
}

DataType* TryAddElementAt(int data, int pos, DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return head;
	}

	DataType* tmp = CreateElement(data);
	if (tmp == NULL)
		return head;

	if (pos == 0)
	{
		DataType* headEl = head;
		tmp->next = headEl;
		head = tmp;
		return head;
	}

	DataType* l = head;
	for (int i = 0; i < pos - 1; i++)
	{
		if (l == NULL)
		{
			printf("ERROR: Index out of list\n");
			return head;
		}

		l = l->next;
	}

	tmp->next = l->next;
	l->next = tmp;
	return head;
}

DataType* TryRemoveElementAt(int pos, DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return head;
	}

	if (pos == 0)
	{
		DataType* headEl = head;
		head = headEl->next;
		free(headEl);
		return head;
	}

	DataType* l = head;
	DataType* tmp = NULL;
	for (int i = 0; i < pos; i++)
	{
		if (l == NULL || l->next == NULL)
		{
			printf("ERROR: Index out of list\n");
			return head;
		}

		tmp = l;
		l = l->next;
	}

	tmp->next = l->next;
	free(l);
	return head;
}

int* TryCheckElementAt(int pos, DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	DataType* l = head;
	for (int i = 0; i < pos; i++)
	{
		if (l->next == NULL || l == NULL)
			return NULL;
		l = l->next;
	}
	return &(l->value);
}

void PrintDataType(DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return;
	}

	DataType* l = head;
	while (l->next != NULL)
	{
		printf("%d ", l->value);
		l = l->next;
	}
	printf("%d\n", l->value);
}

int* GetLength(DataType* head)
{
	if (IsDataTypeNull(head) == 1)
	{
		printf("ERROR: Null exception\n");
		return NULL;
	}

	int count = 0;
	DataType* l = head;
	while (l != NULL)
	{
		l = l->next;
		count++;
	}

	return &count;
}

DataType* Clear(DataType* dataType)
{
	int* length = GetLength(dataType);
	if (length == NULL)
		return;

	DataType* h = dataType;
	for (int i = 0; i < *length; i++)
	{
		h = TryRemoveElementAt(0, h);
	}

	return h;
}

