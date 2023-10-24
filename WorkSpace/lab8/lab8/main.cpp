#include <stdio.h>
#include <stdlib.h>
#include <time.h>	
#include "list.h"
#include "queue.h"

#include <queue>


int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);
void PrintListMatrix(DataType** matrix, int size);

int** GenerateAdjacencyMatrix(int size);
DataType** GenerateListMatrix(int** matrix, int size);

void BFS(int** matrix, int size);
void BFSList(DataType** list, int size);

void BFSLocal(int** matrix, int size);

int main()
{
	srand(time(NULL));

	const int size = 4;
	int** matrix = GenerateAdjacencyMatrix(size);

	printf("Adjacency matrix:\n");
	PrintMatrix(matrix, size, size);

	printf("---- START BFS RUN ----\n");
	BFS(matrix, size);

	printf("\n--------\n\n");

	DataType** list = GenerateListMatrix(matrix, size);
	printf("List matrix:\n");
	PrintListMatrix(list, size);

	printf("---- START BFS RUN ----\n");
	BFSList(list, size);

	printf("\n--------\n\n");

	printf("---- START BFS LOCAL RUN ----\n");
	BFSLocal(matrix, size);

	return 0;
}

#pragma region Matrix work
int** GenerateMatrix(int size_x, int size_y)
{
	int** matrix = (int**)malloc(size_x * sizeof(int*));
	if (matrix == NULL)
		return NULL;

	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = (int*)malloc(size_y * sizeof(int));

		if (matrix[i] == NULL)
			return NULL;
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			matrix[i][j] = 0;
		}
	}

	return matrix;
}

void ClearMatrix(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void PrintMatrix(int** matrix, int size_x, int size_y)
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void PrintListMatrix(DataType** matrix, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		PrintDataType(matrix[i]);
	}
}

int** RemoveVertex(int** matrix, int* size, int r)
{
	int s = *size;
	int** nMatrix = GenerateMatrix(s - 1, s - 1);
	int di = 0, dj = 0;
	for (size_t i = 0; i < s; i++)
	{
		if (i == r)
			i++;
		if (i >= s)
			break;

		for (size_t j = 0; j < s; j++)
		{
			if (j == r)
				j++;
			if (j >= s)
				break;

			nMatrix[di][dj] = matrix[i][j];
			dj++;
		}

		di++;
		dj = 0;
	}

	*size = s - 1;
	return nMatrix;
}
#pragma endregion

#pragma region  MatrixGenerate
int** GenerateAdjacencyMatrix(int size)
{
	int** matrix = GenerateMatrix(size, size);

	if (matrix == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (i == j)
				continue;

			int rnd = rand() % 2;

			matrix[i][j] = rnd;
			if (rnd == 1)
				matrix[j][i] = 1;
		}
	}

	return matrix;
}

DataType** GenerateListMatrix(int** matrix, int size)
{
	DataType** matrixL = (DataType**)malloc(sizeof(DataType*) * size);
	for (int i = 0; i < size; i++)
		matrixL[i] = CreateDataType(i);

	for (int i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 1)
				continue;

			Add(j, matrixL[i]);
		}
	}

	return matrixL;
}
#pragma endregion

#pragma region First Number
void BFSLogic(int** matrix, int size, int vertex, int* used) 
{
	std::queue<int> q;
	q.push(vertex);
	used[vertex] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		printf("%d ", cur);

		for (size_t i = 0; i < size; i++)
		{
			if (matrix[vertex][i] == 1 && used[i] == 0)
			{
				q.push(i);
				used[i] = 1;
			}
		}
	}
}

void BFS(int** matrix, int size)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogic(matrix, size, 0, used);

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == 0)
		{
			printf("\n");
			BFSLogic(matrix, size, i, used);
		}
	}

	printf("\n");
	free(used);
}

void BFSLogicList(DataType** list, int size, int vertex, int* used)
{
	std::queue<int> q;
	q.push(vertex);
	used[vertex] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		printf("%d ", cur);

		int i = 1;
		int* v = TryCheckElementAt(i, list[vertex]);
		while (v != NULL)
		{
			if (v == NULL)
				break;

			if (used[*v] == 0)
			{
				q.push(*v);
				used[*v] = 1;
			}
			i++;
			v = TryCheckElementAt(i, list[vertex]);
		}
	}
}

void BFSList(DataType** list, int size)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogicList(list, size, 0, used);

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == 0)
		{
			printf("\n");
			BFSLogicList(list, size, i, used);
		}
	}

	printf("\n");
	free(used);
}
#pragma endregion

#pragma region Second Number
void BFSLogicLocal(int** matrix, int size, int vertex, int* used)
{
	DataType* q = CreateQueue(vertex);
	used[vertex] = 1;

	while (IsEmpty(q) == 0)
	{
		int cur;
		q = Dequeue(q, &cur);

		printf("%d ", cur);

		for (size_t i = 0; i < size; i++)
		{
			if (matrix[vertex][i] == 1 && used[i] == 0)
			{
				Enqueue(i, q);
				used[i] = 1;
			}
		}
	}
}

void BFSLocal(int** matrix, int size)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogic(matrix, size, 0, used);

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == 0)
		{
			printf("\n");
			BFSLogic(matrix, size, i, used);
		}
	}

	printf("\n");
	free(used);
}
#pragma endregion
