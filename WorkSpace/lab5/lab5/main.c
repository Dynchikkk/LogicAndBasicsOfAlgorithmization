#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 2

int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);

int** GenerateAdjacencyMatrix(int size);
int CalculateAdjSize(int** matrix, int size);
void CheckAdjPeaks(int** matrix, int size);

int** GenerateIncidenceMatrix(int** matrix, int size);
int RebrCount(int** matrix, int size);
int CalculateIncSize(int** matrix, int size_x, int size_y);
void CheckIncPeaks(int** matrix, int size_x, int size_y);

int main(){
	srand(time(NULL));

	int matrixSize = 0;
	printf("Insert Matrix size: ");
	scanf("%d", &matrixSize);
	if (matrixSize < MATRIX_SIZE)
		matrixSize = MATRIX_SIZE;

	printf("\n---- GENERATING. SIZE %d ----\n\n", matrixSize);

	printf("----- ADJACENCY MATRIX -----\n");
	int** matrixAdj = GenerateAdjacencyMatrix(matrixSize);

	printf("---- Print matrix ----\n");
	PrintMatrix(matrixAdj, matrixSize, matrixSize);

	printf("---- Calculate matrix size ----\n");
	printf("Size: %d\n", CalculateAdjSize(matrixAdj, matrixSize));

	printf("---- Peaks info ----\n");
	CheckAdjPeaks(matrixAdj, matrixSize);

	printf("\n----- INCEDENCE MATRIX -----\n");
	int r = RebrCount(matrixAdj, matrixSize);
	int** matrixInc = GenerateIncidenceMatrix(matrixAdj, matrixSize);

	printf("---- Print matrix ----\n");
	PrintMatrix(matrixInc, matrixSize, r);

	printf("---- Calculate matrix size ----\n");
	printf("Size: %d\n", CalculateIncSize(matrixInc, matrixSize, r));

	printf("---- Peaks info ----\n");
	CheckIncPeaks(matrixInc, matrixSize, r);

	ClearMatrix(matrixAdj, matrixSize);
	ClearMatrix(matrixInc, matrixSize);

	return 0;
}

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

#pragma region Adjacency Matrix

int** GenerateAdjacencyMatrix(int size)
{
	int** matrix = GenerateMatrix(size, size);
	int chance = 50;
	printf("Rebro spawn chance (0-100%): ");
	scanf("%d", &chance);


	if (matrix == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (i == j)
				continue;

			int rnd = rand() % 100;
			if (rnd < chance)
				rnd = 1;
			else
				rnd = 0;

			matrix[i][j] = rnd;
			if (rnd == 1)
				matrix[j][i] = 1;
		}
	}

	return matrix;
}

int CalculateAdjSize(int** matrix, int size)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				count++;
			}
		}
	}

	return count;
}

void CheckAdjPeaks(int** matrix, int size)
{
	int isolate = 0;
	int end = 0;
	int max = 0;

	for (int i = 0; i < size; i++)
	{
		int c = 0;
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
				c++;
		}

		if (c == 0)
			isolate++;
		else if (c == 1)
			end++;

		if (c == size - 1)
		{
			max++;
		}
	}

	printf("Isolate peaks: %d\n", isolate);
	printf("End peaks: %d\n", end);
	printf("Dominant peaks: %d\n", max);
}
#pragma endregion

#pragma region Incidence Matrix

int RebrCount(int** matrix, int size)
{
	int rCount = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
				rCount++;
		}
	}
	return rCount / 2;
}

int** GenerateIncidenceMatrix(int** matrix, int size) 
{
	int rCount = RebrCount(matrix, size);

	int** incMatrix = GenerateMatrix(size, rCount);

	int curR = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				incMatrix[i][curR] = 1;
				incMatrix[j][curR] = 1;
				curR++;
			}
		}
	}

	return incMatrix;
}

int CalculateIncSize(int** matrix, int size_x, int size_y)
{
	int count = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (matrix[i][j] == 1)
				count++;
		}
	}
	return count / 2;
}

void CheckIncPeaks(int** matrix, int size_x, int size_y)
{
	int isolate = 0;
	int end = 0;
	int max = 0;

	for (int i = 0; i < size_x; i++)
	{
		int c = 0;
		for (int j = 0; j < size_y; j++)
		{
			if (matrix[i][j] == 1)
				c++;
		}

		if (c == 0)
			isolate++;
		else if (c == 1)
			end++;

		if (c == size_x - 1)
		{
			max++;
		}
	}

	printf("Isolate peaks: %d\n", isolate);
	printf("End peaks: %d\n", end);
	printf("Dominant peaks: %d\n", max);
}
#pragma endregion
