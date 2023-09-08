#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int SINGLE_ARRAY_SIZE;
const int DOUBLE_ARRAY_SIZE_X;
const int DOUBLE_ARRAY_SIZE_Y;

#pragma region SingleArray
int* GenerateSingleArray(int size)
{
	int* array = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		array[i] = 10 + rand() % 90;
	}

	return array;
}

int FindMinMaxDiff(int* array, int size)
{
	int min = *array;
	int max = *array;
	for (int i = 0; i < size; i++)
	{
		int curEl = array[i];
		if (curEl < min)
			min = curEl;
		if (curEl > max)
			max = curEl;
	}

	printf("Min: %d, Max: %d\n", min, max);
	return max - min;
}
#pragma endregion

#pragma region DoubleArray
int** GenerateDoubleArray(int sizeX, int sizeY)
{
	int** array = (int**)malloc(sizeX * sizeof(int*));

	for (int i = 0; i < sizeX; i++)
	{
		array[i] = GenerateSingleArray(sizeY);
	}

	return array;
}

void CalculateColumnRowSum(int** array, int sizeX, int sizeY)
{
	int rowSum = 0;
	printf("Rows sum:\n");
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			rowSum += array[i][j];
		}
		printf("%d: %d\n", i + 1, rowSum);
		rowSum = 0;
	}
	printf("----------\n");

	printf("Columns sum:\n");
	int colSum = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			colSum += array[j][i];
		}
		printf("%d: %d\n", i + 1, colSum);
		colSum = 0;
	}
}
#pragma endregion

void writeArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void Part1()
{
	srand(time(NULL));

	// Single array part
	printf("----------\n");

	printf("Insert single array length: ");
	scanf("%d",&SINGLE_ARRAY_SIZE);

	int* singleArray = GenerateSingleArray(SINGLE_ARRAY_SIZE);
	printf("Array: ");
	writeArray(singleArray, SINGLE_ARRAY_SIZE);

	printf("Min/Max difference: %d \n", FindMinMaxDiff(singleArray, SINGLE_ARRAY_SIZE));

	free(singleArray);

	printf("----------\n");

	// Double array size
	printf("----------\n");

	printf("Insert double array length x: ");
	scanf("%d", &DOUBLE_ARRAY_SIZE_X);
	getchar();
	printf("Insert double array length y: ");
	scanf("%d", &DOUBLE_ARRAY_SIZE_Y);

	int** doubleArray = GenerateDoubleArray(DOUBLE_ARRAY_SIZE_X, DOUBLE_ARRAY_SIZE_Y);
	printf("Array:\n");
	for (int i = 0; i < DOUBLE_ARRAY_SIZE_X; i++)
	{
		writeArray(doubleArray[i], DOUBLE_ARRAY_SIZE_Y);
	}

	printf("----------\n");
	CalculateColumnRowSum(doubleArray, DOUBLE_ARRAY_SIZE_X, DOUBLE_ARRAY_SIZE_Y);

	for (int i = 0; i < DOUBLE_ARRAY_SIZE_X; i++)
	{
		free(doubleArray[i]);
	}
	free(doubleArray);

	printf("----------\n");
}