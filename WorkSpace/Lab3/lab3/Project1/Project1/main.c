#include <stdio.h>
#include "list.h"
#include "prior_queue.h"
#include "queue.h"
#include "stack.h"

int main()
{
#pragma region list
	printf("---- List part ----\n");
	DataType* l = CreateDataType(1);
	Add(2, l);
	Add(3, l);
	PrintDataType(l);

	l = TryAddElementAt(0, 0, l);
	l = TryAddElementAt(1, 10, l);
	PrintDataType(l);

	printf("%d\n", *TryCheckElementAt(1, l));

	l = TryRemoveElementAt(0, l);
	PrintDataType(l);

	printf("%d\n", *GetLength(l));

	l = TryRemoveElementAt(0, l);
	l = TryRemoveElementAt(0, l);
	l = TryRemoveElementAt(0, l);
	l = TryRemoveElementAt(0, l);

	l = Clear(l);
#pragma endregion

#pragma region prior queue
	printf("\n---- Prior queue part ----\n");
	DataType* pQ = CreatePrQueue(1);
	EnqueuePr(20, pQ);
	EnqueuePr(10, pQ);
	EnqueuePr(100, pQ);

	PrintDataType(pQ);

	int valPQ = 0;
	pQ = DequeuePr(pQ, &valPQ);
	printf("%d\n", valPQ);
	pQ = DequeuePr(pQ, &valPQ);
	printf("%d\n", valPQ);
	pQ = DequeuePr(pQ, &valPQ);
	printf("%d\n", valPQ);
	pQ = DequeuePr(pQ, &valPQ);
	printf("%d\n", valPQ);
	pQ = DequeuePr(pQ, &valPQ);
	pQ = DequeuePr(pQ, &valPQ);
	pQ = Clear(pQ);
#pragma endregion

#pragma region queue
	printf("\n---- Queue part ----\n");
	DataType* q = CreateQueue(1);
	Enqueue(20, q);
	Enqueue(10, q);
	Enqueue(100, q);
	PrintDataType(q);

	int valQ = 0;
	q = Dequeue(q, &valQ);
	printf("%d\n", valQ);
	q = Dequeue(q, &valQ);
	printf("%d\n", valQ);
	q = Dequeue(q, &valQ);
	printf("%d\n", valQ);
	q = Dequeue(q, &valQ);
	printf("%d\n", valQ);
	q = Dequeue(q, &valQ);
	q = Dequeue(q, &valQ);
	q = Clear(q);
#pragma endregion

#pragma region stack
	printf("\n---- Stack part ----\n");

	DataType* s = CreateStack(1);
	Push(20, s);
	Push(10, s);
	Push(100, s);
	PrintDataType(s);

	int valS = 0;
	s = Pop(s, &valS);
	printf("%d\n", valS);
	s = Pop(s, &valS);
	printf("%d\n", valS);
	s = Pop(s, &valS);
	printf("%d\n", valS);
	s = Pop(s, &valS);
	printf("%d\n", valS);
	s = Pop(s, &valS);
	s = Pop(s, &valS);
	s = Clear(s);
#pragma endregion

	return 0;
}