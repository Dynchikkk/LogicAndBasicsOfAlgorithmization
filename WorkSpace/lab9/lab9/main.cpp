#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>	
#include "list.h"

#include <queue>

int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);
void PrintListMatrix(DataType** matrix, int size);

int** GenerateAdjacencyMatrix(int size);
DataType** GenerateListMatrix(int** matrix, int size);

void BFS(int** matrix, int size, int needPrint, int in, int out);

int main()
{
	srand(time(NULL));

	const int size = 5;
	int** matrix = GenerateAdjacencyMatrix(size);

	printf("Adjacency matrix:\n");
	PrintMatrix(matrix, size, size);

	DataType** list = GenerateListMatrix(matrix, size);
	printf("List matrix:\n");
	PrintListMatrix(list, size);

	printf("Insert in and out vertex: ");
	int in = 0, out = 0;
	scanf("%d %d", &in, &out);

	printf("\n");
	BFS(matrix, size, 1, in, out);

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

#pragma region  FirstNumber
DataType* BFSLogic(int** matrix, int size, int in, int out, int* used, int* pathSize)
{
	std::queue<int> q;

	int* dst = (int*)malloc(size * sizeof(int));
	memset(dst, -1, size * sizeof(int));

	int* pr = (int*)malloc(size* sizeof(int));
	memset(pr, NULL, size * sizeof(int));

	q.push(in);
	used[in] = 1;
	dst[in] = 0;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (size_t i = 0; i < size; i++)
		{
			if (matrix[cur][i] == 1 && used[i] == 0)
			{
				q.push(i);
				used[i] = 1;
				dst[i] = dst[cur] + 1;
				pr[i] = cur;
			}
		}
	}

	int cur = out;
	DataType* path = CreateDataType(cur);

	while (cur != in)
	{
		cur = pr[cur];
		Add(cur, path);
	}

	int* s = GetLength(path);
	if (s == NULL)
		*pathSize = 0;
	else
		*pathSize = *s;

	free(dst);
	free(pr);

	return path;
}

void BFS(int** matrix, int size, int needPrint, int in, int out)
{
	int* used = (int*)calloc(size, sizeof(int));

	int count = 0;
	DataType* path = BFSLogic(matrix, size, in, out, used, &count);
	printf("\n");

	if (count == NULL)
	{
		printf("There is no path\n");
	}
	else 
	{
		for (size_t i = 0, j = count - 1; i < count; i++, j--)
		{
			printf("%d ", *TryCheckElementAt(j, path));
		}
		printf("\n");
	}

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

void BFSList(DataType** list, int size, int entryPoint)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogicList(list, size, entryPoint, used);

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
