#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

Tree* CreateNode(int value)
{
	Tree* tmp = (Tree*)malloc(sizeof(Tree));
	tmp->value = value;
	tmp->left = NULL;
	tmp->right = NULL;
}

Tree* CreateTree(int val)
{
	return CreateNode(val);
}

Tree* AddNode(int val, Tree* root)
{
	if(root != NULL && root->value == val)
	{
		printf("ERROR: same value in tree\n");
		return root;
	}

	if (root == NULL)
		root = CreateNode(val);
	else if (val < root->value)
		root->left = AddNode(val, root->left);
	else
		root->right = AddNode(val, root->right);

	return(root);
}

Tree* SearchNode(int val, Tree* root)
{
	if (root == NULL)
		return NULL;

	if (root->value == val)
		return root;

	if (val < root->value)
		return SearchNode(val, root->left);
	else
		return SearchNode(val, root->right);
}

int EntryCount(int value, Tree* root, int entry)
{
	if (root == NULL)
		return -1;

	if (root->value == value)
		return entry + 1;

	if (value < root->value)
		return EntryCount(value, root->left, entry + 1);
	else
		return EntryCount(value, root->right, entry + 1);
}

void ClearTree(Tree* root)
{
	if (root == NULL)
		return;

	ClearTree(root->left);
	ClearTree(root->right);
	free(root);
}

void TreePrint(Tree* root, int tabs)
{
	for (int i = 0; i < tabs * 2; i++)
		printf(" ");

	if (root == NULL)
	{
		printf("-\n");
		return;
	}

	printf("%d\n", root->value);

	TreePrint(root->left, tabs + 1);
	TreePrint(root->right, tabs + 1);
}

void PrintOneNode(Tree* node)
{
	if (node == NULL)
	{
		printf("No node\n");
		return;
	}

	printf("%d\n", node->value);
	if (node->left != NULL)
	{
		printf("%d", node->left->value);
	}
	printf("  ");
	if (node->right != NULL)
	{
		printf("%d", node->right->value);
	}
	printf("\n");
}

