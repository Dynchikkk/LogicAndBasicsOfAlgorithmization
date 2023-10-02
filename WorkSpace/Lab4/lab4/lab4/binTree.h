#ifndef BIN_TREE
#define BIN_TREE

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
} Tree;

Tree* CreateTree(int val);

Tree* AddNode(int val, Tree* root);

Tree* SearchNode(int val, Tree* root);

int EntryCount(int value, Tree* root, int entry);

void TreePrint(Tree* root, int tabs);

void ClearTree(Tree* root);

void PrintOneNode(Tree* root);

void TreeWalk(Tree* root);

#endif 

