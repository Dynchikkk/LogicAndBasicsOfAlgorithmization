#ifndef STACK
#define STACK
#include "list.h"

DataType* CreateStack(int data);

void Push(int num, DataType* prQueue);

DataType* Pop(DataType* prQueue, int val);

#endif
