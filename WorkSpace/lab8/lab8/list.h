#ifndef LIST
#define LIST

typedef struct Node {
	int value;
	struct Node* next;
} DataType;

int IsDataTypeNull(DataType* head);

DataType* CreateDataType(int data);

void Add(int data, DataType* head);

DataType* TryAddElementAt(int data, int pos, DataType* head);

DataType* TryRemoveElementAt(int pos, DataType* head);

int* TryCheckElementAt(int pos, DataType* head);

void PrintDataType(DataType* head);

int* GetLength(DataType* head);

DataType* Clear(DataType* head);

#endif

