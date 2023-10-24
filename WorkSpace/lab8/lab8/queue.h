#ifndef QUEUE
#define QUEUE
#include "list.h"

DataType* CreateQueue(int data);

void Enqueue(int num, DataType* queue);

DataType* Dequeue(DataType* queue, int* val);

int IsEmpty(DataType* queue);

#endif
