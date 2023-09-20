#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE
#include "list.h"

DataType* CreatePrQueue(int data);

void EnqueuePr(int num, DataType* prQueue);

DataType* DequeuePr(DataType* prQueue, int*val);

#endif