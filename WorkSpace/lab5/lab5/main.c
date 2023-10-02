#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 4

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

	printf("----- ADJACENCY MATRIX -----\n");
	int** matrixAdj = GenerateAdjacencyMatrix(MATRIX_SIZE);

	printf("---- Print matrix ----\n");
	PrintMatrix(matrixAdj, MATRIX_SIZE, MATRIX_SIZE);

	printf("---- Calculate matrix size ----\n");
	printf("Size: %d\n", CalculateAdjSize(matrixAdj, MATRIX_SIZE));

	printf("---- Peaks info ----\n");
	CheckAdjPeaks(matrixAdj, MATRIX_SIZE);

	printf("\n----- INCEDENCE MATRIX -----\n");
	int r = RebrCount(matrixAdj, MATRIX_SIZE);
	int** matrixInc = GenerateIncidenceMatrix(matrixAdj, MATRIX_SIZE);

	printf("---- Print matrix ----\n");
	PrintMatrix(matrixInc, MATRIX_SIZE, r);

	printf("---- Calculate matrix size ----\n");
	printf("Size: %d\n", CalculateIncSize(matrixInc, MATRIX_SIZE, r));

	printf("---- Peaks info ----\n");
	CheckIncPeaks(matrixInc, MATRIX_SIZE, r);

	ClearMatrix(matrixAdj, MATRIX_SIZE);
	ClearMatrix(matrixInc, r);

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

	if (matrix == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (i == j)
				continue;

			int rnd = rand() % 2;
			int izolate = rand() % 2;

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
	int** rebra = GenerateMatrix(size, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			rebra[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (rebra[i][j] == 1)
			{
				count++;
				rebra[j][i] = 0;
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
	int maxCount = 0;

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

		if (c > maxCount)
		{
			maxCount = c;
			max = i;
		}
	}

	printf("Isolate peaks: %d\n", isolate);
	printf("End peaks: %d\n", end);
	printf("Dominant peaks: %d\n", max + 1);
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
	int maxCount = 0;

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

		if (c > maxCount)
		{
			maxCount = c;
			max = i;
		}
	}

	printf("Isolate peaks: %d\n", isolate);
	printf("End peaks: %d\n", end);
	printf("Dominant peaks: %d\n", max + 1);
}
#pragma endregion
