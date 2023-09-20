#ifndef QUEUE
#define QUEUE
#include "list.h"

DataType* CreateQueue(int data);

void Enqueue(int num, DataType* prQueue);

DataType* Dequeue(DataType* prQueue, int* val);

#endif
