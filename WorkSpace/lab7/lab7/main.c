#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "list.h"

int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);
void PrintListMatrix(DataType** matrix, int size);

int** GenerateAdjacencyMatrix(int size);
DataType** GenerateListMatrix(int** matrix, int size);

void DFSadj(int** matrix, int matrixSize);
void DFSlist(DataType** list, int listSize);

int main()
{
	srand(time(NULL));

	const int size = 4;
	int** matrix = GenerateAdjacencyMatrix(size);
	PrintMatrix(matrix, size, size);

	printf("---- START DEPTH RUN ----\n");
	DFSadj(matrix, size);

	printf("\n--------\n\n");

	DataType** list = GenerateListMatrix(matrix, size);
	PrintListMatrix(list, size);

	printf("---- START DEPTH RUN ----\n");
	DFSlist(list, size);

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

#pragma region FirstNumber
void DFSCuroadj(int start, int* visited, int** matrix, int matrixSize)
{
	visited[start] = 1;
	printf("%d ", start);

	for (int r = 0; r <= matrixSize; r++)
	{
		if ((matrix[start][r] != 0) && (visited[r] == 0))
		{
			DFSCuroadj(r, visited, matrix, matrixSize);
		}
	}
}

void DFSadj(int** matrix, int matrixSize)
{
	int* vis = (int*)calloc(matrixSize, sizeof(int));

	DFSCuroadj(0, vis, matrix, matrixSize);

	for (int i = 0; i < matrixSize; i++)
	{
		if (vis[i] == 0)
		{
			printf("\n");
			DFSCuroadj(i, vis, matrix, matrixSize);
		}
	}

	printf("\n");
	free(vis);
}

void DFSCurolist(int start, int* visited, DataType** list, int listSize)
{
	visited[start] = 1;
	printf("%d ", start);

	int i = 1;

	int* v = TryCheckElementAt(i, list[start]);
	while (v != NULL)
	{
		if (v == NULL)
			break;

		if (visited[*v] == 0)
		{
			DFSCurolist(*v, visited, list, listSize);
		}

		i++;
		v = TryCheckElementAt(i, list[start]);
	}
}

void DFSlist(DataType** list, int listSize)
{
	int* vis = (int*)calloc(listSize, sizeof(int));
	DFSCurolist(0, vis, list, listSize);

	for (int i = 0; i < listSize; i++)
	{
		if (vis[i] == 0)
		{
			printf("\n");
			DFSCurolist(i, vis, list, listSize);
		}
	}

	printf("\n");
	free(vis);
}


#pragma endregion

