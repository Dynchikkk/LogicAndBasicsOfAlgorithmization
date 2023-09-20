#ifndef STACK
#define STACK
#include "list.h"

DataType* CreateStack(int data);

void Push(int num, DataType* stack);

DataType* Pop(DataType* stack, int* val);

#endif
