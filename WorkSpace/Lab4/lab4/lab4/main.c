#include <stdio.h>
#include "binTree.h"

int main()
{
	Tree* root = CreateTree(50);

	printf("---- Tree print ----\n");
	root = AddNode(10, root);
	root = AddNode(12, root);
	root = AddNode(11, root);
	root = AddNode(20, root);
	root = AddNode(19, root);
	root = AddNode(25, root);
	root = AddNode(24, root);
	root = AddNode(100, root);
	root = AddNode(60, root);
	root = AddNode(110, root);
	TreePrint(root, 0);

	printf("---- Finded node ----\n");
	Tree* find = SearchNode(100, root);
	PrintOneNode(find);

	printf("---- Entry count ----\n");
	printf("Entry count of %d: %d\n", 19, EntryCount(19, root, 0));

	printf("---- Tree walk ----\n");
	TreeWalk(root);

	ClearTree(root);

	return 0;
}