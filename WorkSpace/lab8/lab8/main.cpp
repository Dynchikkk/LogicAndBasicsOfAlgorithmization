#define _CRT_SECURE_NO_WARNINGS

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

void BFS(int** matrix, int size, int needPrint, int entryPoint);
void BFSList(DataType** list, int size, int entryPoint);

void BFSLocal(int** matrix, int size, int needPrint, int entryPoint);

void AutoTest();

double CalculateSpeed(void (*func)(int**, int, int, int), int** matrix, int size)
{
	double time_spent = 0.0;

	clock_t begin = clock();
	func(matrix, size, 0, 0);
	clock_t end = clock();

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

int main()
{
	srand(time(NULL));

	const int size = 4;
	int** matrix = GenerateAdjacencyMatrix(size);

	printf("Adjacency matrix:\n");
	PrintMatrix(matrix, size, size);

	printf("\nInsert entry point: ");
	int entryPoint = 0;
	scanf("%d", &entryPoint);

	printf("\n---- START BFS RUN ----\n");
	BFS(matrix, size, 1, entryPoint);

	printf("\n");

	DataType** list = GenerateListMatrix(matrix, size);
	printf("List matrix:\n");
	PrintListMatrix(list, size);

	printf("---- START BFS RUN ----\n");
	BFSList(list, size, entryPoint);

	printf("\n");

	printf("---- START BFS LOCAL RUN ----\n");
	BFSLocal(matrix, size, 1, entryPoint);

	printf("\n------------- AUTO TEST --------------\n");
	AutoTest();

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
void BFSLogic(int** matrix, int size, int vertex, int* used, int needPrint)
{
	std::queue<int> q;
	q.push(vertex);
	used[vertex] = 1;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		if(needPrint == 1)
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

void BFS(int** matrix, int size, int needPrint, int entryPoint)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogic(matrix, size, entryPoint, used , needPrint);

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == 0)
		{
			if(needPrint == 1)
				printf("\n");
			BFSLogic(matrix, size, i, used, needPrint);
		}
	}

	if (needPrint == 1)
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

#pragma region Second Number
void BFSLogicLocal(int** matrix, int size, int vertex, int* used, int needPrint)
{
	DataType* q = CreateQueue(vertex);
	used[vertex] = 1;

	while (IsEmpty(q) == 0)
	{
		int cur;
		q = Dequeue(q, &cur);

		if(needPrint == 1)
			printf("%d ", cur);

		for (size_t i = 0; i < size; i++)
		{
			if (matrix[vertex][i] == 1 && used[i] == 0)
			{
				q = Enqueue(i, q);
				used[i] = 1;
			}
		}
	}
}

void BFSLocal(int** matrix, int size, int needPrint, int entryPoint)
{
	int* used = (int*)calloc(size, sizeof(int));

	BFSLogicLocal(matrix, size, entryPoint, used, needPrint);

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == 0)
		{
			if (needPrint == 1)
				printf("\n");
			BFSLogicLocal(matrix, size, i, used, needPrint);
		}
	}

	if (needPrint == 1)
		printf("\n");
	free(used);
}
#pragma endregion

#pragma region AutoTest
void AutoTest() 
{
	printf("--------------------------------------\n");
	printf("| size |time with class|time no class|\n");

	for (size_t i = 2000; i <= 20000; i+= 2000)
	{
		
		int** matrix = GenerateAdjacencyMatrix(i);

		double def = CalculateSpeed(BFS, matrix, i);
		double own = CalculateSpeed(BFSLocal, matrix, i);

		printf("|%6d|", i);
		printf("%12f s.", def);

		ClearMatrix(matrix, i);
		printf("|%10f s.|\n", own);
	}
	printf("--------------------------------------\n");
}
#pragma endregion

