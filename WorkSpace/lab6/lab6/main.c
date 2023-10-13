#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);
void PrintListMatrix(DataType** matrix, int size);

int** GenerateAdjacencyMatrix(int size);
DataType** GenerateListMatrix(int** matrix, int size);

int** Identification(int** matrix, int* size, int x, int y);
int** Tightening(int** matrix, int* size, int x, int y);
int** Splitting(int** matrix, int* size, int x, int y);
DataType** IdentificationL(DataType** matrix, int* size, int x, int y);
DataType** TighteningL(DataType** matrix, int* size, int x, int y);
DataType** SplittingL(DataType** matrix, int* size, int x, int y);

int** Union(int** matrix1, int size1, int** matrix2, int size2, int* outSize);
int** Intersection(int** matrix1, int size1, int** matrix2, int size2, int* outSize);
int** RoundSum(int** matrix1, int size1, int** matrix2, int size2, int* outSize);

int** Multiplication(int** matrix1, int size1, int** matrix2, int size2, int* sizeOut);

int main()
{
	//srand(time(NULL));

	int matrixSize1 = 0;
	printf("Insert size of first matrix: ");
	scanf("%d", &matrixSize1);
	int** matrix1 = GenerateAdjacencyMatrix(matrixSize1);
	printf("--- Matrix 1 ---\n");
	PrintMatrix(matrix1, matrixSize1, matrixSize1);
	printf("-------\n");

	int matrixSize2 = 0;
	printf("Insert size of second matrix: ");
	scanf("%d", &matrixSize2);
	int** matrix2 = GenerateAdjacencyMatrix(matrixSize2);
	printf("--- Matrix 2 ---\n");
	PrintMatrix(matrix2, matrixSize2, matrixSize2);
	printf("-------\n");

	int matrixSizeL1 = matrixSize1;
	int matrixSizeL2 = matrixSize2;
	DataType** matrixL1 = GenerateListMatrix(matrix1, matrixSizeL1);
	DataType** matrixL2 = GenerateListMatrix(matrix2, matrixSizeL2);
	printf("--- List Matrix 1---\n");
	PrintListMatrix(matrixL1, matrixSizeL1);
	printf("-------\n");
	printf("--- List Matrix 2---\n");
	PrintListMatrix(matrixL2, matrixSizeL2);
	printf("-------\n");

	int answ = -1;
	while (answ != 0)
	{

		printf("Choose Action\n1 - Identification\n2 - Tightening\n3 - Splitting\n");
		printf("4 - Identification list\n5 - Tightening list\n6 - Splitting list\n7 - Union\n");
		printf("8 - Intersection\n9 - RoundSum\n10 - Multiplication\n0 - exit\n");
		scanf("%d", &answ);
		system("cls");
		switch (answ)
		{
			case 1:
				printf("Identification matrix2. Row = 0, col = 3\n");
				printf("-------\n");
				matrix2 = Identification(matrix2, &matrixSize2, 0, 3);
				PrintMatrix(matrix2, matrixSize2, matrixSize2);
				printf("-------\n");
				break;

			case 2:
				printf("Tightening matrix2. Row = 0, col = 1\n");
				printf("-------\n");
				matrix2 = Tightening(matrix2, &matrixSize2, 0, 1);
				PrintMatrix(matrix2, matrixSize2, matrixSize2);
				printf("-------\n");
				break;

			case 3:
				printf("Splitting matrix2. Row = 0, col = 1\n");
				printf("-------\n");
				matrix2 = Splitting(matrix2, &matrixSize2, 0, 1);
				PrintMatrix(matrix2, matrixSize2, matrixSize2);
				printf("-------\n");
				break;

			case 4:
				printf("Identification matrixList2. Row = 0, col = 3\n");
				printf("-------\n");
				matrixL2 = IdentificationL(matrixL2, &matrixSize2, 0, 3);
				PrintListMatrix(matrixL2, matrixSize2);
				printf("-------\n");
				break;

			case 5:
				printf("Tightening matrixList2. Row = 0, col = 1\n");
				printf("-------\n");
				matrixL2 = TighteningL(matrixL2, &matrixSize2, 0, 1);
				PrintListMatrix(matrixL2, matrixSize2);
				printf("-------\n");
				break;

			case 6:
				printf("Splitting matrixList2. Row = 0, col = 1\n");
				printf("-------\n");
				matrixL2 = SplittingL(matrixL2, &matrixSize2, 0, 1);
				PrintListMatrix(matrixL2, matrixSize2);
				printf("-------\n");
				break;

			case 7:
			{
				printf("Union matrix1 and matrix2\n");
				printf("-------\n");
				int uSize = 0;
				int** uMatrix = Union(matrix1, matrixSize1, matrix2, matrixSize2, &uSize);
				PrintMatrix(uMatrix, uSize, uSize);
				printf("-------\n");
				break;
			}

			case 8:
			{
				printf("Intersection matrix1 and matrix2\n");
				printf("-------\n");
				int iSize = 0;
				int** iMatrix = Intersection(matrix1, matrixSize1, matrix2, matrixSize2, &iSize);
				PrintMatrix(iMatrix, iSize, iSize);
				printf("-------\n");
				break;
			}

			case 9:
			{
				printf("Round sum matrix1 and matrix2\n");
				printf("-------\n");
				int rsSize = 0;
				int** rsMatrix = RoundSum(matrix1, matrixSize1, matrix2, matrixSize2, &rsSize);
				PrintMatrix(rsMatrix, rsSize, rsSize);
				printf("-------\n");
				break;
			}

			case 10:
			{
				printf("Multiplication matrix1 and matrix2\n");
				printf("-------\n");
				int mSize = 0;
				int** m3 = GenerateMatrix(matrixSize2, matrixSize2);
				m3[0][0] = 0;
				m3[0][1] = 1;
				m3[0][2] = 0;
				m3[1][0] = 1;
				m3[1][1] = 0;
				m3[1][2] = 1;
				m3[2][0] = 0;
				m3[2][1] = 1;
				m3[2][2] = 0;
				int** mMatrix = Multiplication(matrix1, matrixSize1, m3, matrixSize2, &mSize);
				PrintMatrix(mMatrix, mSize, mSize);
				printf("-------\n");
				break;
			}

			default:
				break;
		}
	}

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

#pragma region First number
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

#pragma region Second Number
int** Identification(int** matrix, int* size, int x, int y)
{
	int s = *size;

	if (y < x)
	{
		int t = x;
		x = y;
		y = t;
	}

	int** nMatrix = GenerateMatrix(s - 1, s - 1);
	int di = 0, dj = 0;
	for (size_t i = 0; i < s; i++)
	{
		if (i == x || i == y)
			i++;
		if (i == x || i == y)
			i++;

		if (i >= s)
			break;

		for (size_t j = 0; j < s; j++)
		{
			if (j == x || j == y)
				j++;
			if (j == x || j == y)
				j++;

			if (j >= s)
				break;

			nMatrix[di][dj] = matrix[i][j];
			dj++;
		}

		di++;
		dj = 0;
	}

	int d = 0;
	for (int i = 0; i < s; i++)
	{
		if (i == x || i == y)
			i++;
		if (i == x || i == y)
			i++;

		if (i >= s)
			break;

		if (matrix[x][i] == 1)
		{
			nMatrix[s - 2][d] = 1;
			nMatrix[d][s - 2] = 1;
		}

		if (matrix[y][i] == 1)
		{
			nMatrix[s - 2][d] = 1;
			nMatrix[d][s - 2] = 1;
		}
		d++;
	}
	*size = *size - 1;
	return nMatrix;
}

int** Tightening(int** matrix, int* size, int x, int y)
{
	if (matrix[x][y] != 1)
		return matrix;

	return Identification(matrix, size, x, y);
}

int** Splitting(int** matrix, int* size, int x, int y)
{
	if (matrix[x][y] != 1)
		return matrix;

	int s = *size;
	matrix = (int**)realloc(matrix, (s + 1) * sizeof(int*));
	matrix[s] = (int*)malloc(s * sizeof(int));
	for (size_t i = 0; i < s; i++)
		matrix[s][i] = 0;

	for (size_t i = 0; i < s + 1; i++)
	{
		matrix[i] = (int*)realloc(matrix[i], (s + 1) * sizeof(int));
		matrix[i][s] = 0;
	}

	matrix[s][x] = 1;
	matrix[x][s] = 1;
	matrix[s][y] = 1;
	matrix[y][s] = 1;

	*size = *size + 1;
	return matrix;

}

DataType** IdentificationL(DataType** matrix, int* size, int x, int y)
{
	int s = *size;
	if (y < x)
	{
		int t = x;
		x = y;
		y = t;
	}

	DataType** matrixL = (DataType**)malloc(sizeof(DataType*) * s - 1);
	for (int i = 0; i < s - 1; i++)
		matrixL[i] = CreateDataType(i);
	
	int d = 0;
	for (size_t i = 0; i < s; i++)
	{
		if (i == x || i == y)
			continue;

		for (size_t j = 1; j < s; j++)
		{
			int* val = TryCheckElementAt(j, matrix[i]);
			if (val == NULL)
				break;

			if (*val == x || *val == y)
				continue;

			if (*val >= x)
				*val -= 1;
			if (*val >= y)
				*val -= 1;

			if (val < 0)
				continue;

			Add(*val, matrixL[d]);
		}
		d++;
	}

	for (size_t i = 1; i < s; i++)
	{
		int* val = TryCheckElementAt(i, matrix[x]);
		if (val == NULL)
			break;

		if (*val >= x)
			*val -= 1;
		if (*val >= y)
			*val -= 1;

		if (*val < 0)
			continue;

		int bool = 0;

		for (size_t j = 1; j < s - 1; j++)
		{
			int* cVal = TryCheckElementAt(j, matrixL[s - 2]);
			if (cVal == NULL)
			{
				break;
			}

			if (*cVal == *val)
			{
				bool = 1;
				break;
			}
		}

		if (bool == 1)
			continue;

		Add(*val, matrixL[s - 2]);
	}

	for (size_t i = 1; i < s; i++)
	{
		int* val = TryCheckElementAt(i, matrix[y]);
		if (val == NULL)
			break;

		if (*val >= x)
			*val -= 1;
		if (*val >= y)
			*val -= 1;

		if (*val < 0)
			continue;

		int bool = 0;

		for (size_t j = 1; j < s - 1; j++)
		{
			int* cVal = TryCheckElementAt(j, matrixL[s - 2]);
			if (cVal == NULL)
			{
				break;
			}

			if (*cVal == *val)
			{
				bool = 1;
				break;
			}
		}

		if (bool == 1)
			continue;

		Add(*val, matrixL[s - 2]);
	}

	for (int i = 1; i < s - 1; i++)
	{
		int* vert = TryCheckElementAt(i, matrixL[s - 2]);
		if (vert == NULL)
			return;

		Add(s - 2, matrixL[*vert]);
	}
	

	*size = *size - 1;
	return matrixL;
}

DataType** TighteningL(DataType** matrix, int* size, int x, int y)
{
	for (int i = 0; i < *size; i++)
	{
		int* val = TryCheckElementAt(i, matrix[x]);
		if (val == NULL)
			break;

		if (*val == y)
			return IdentificationL(matrix, size, x, y);
	}
}

DataType** SplittingL(DataType** matrix, int* size, int x, int y)
{
	int bool = 1;
	for (int i = 0; i < *size; i++)
	{
		int* val = TryCheckElementAt(i, matrix[x]);
		if (val == NULL)
			break;

		if (*val == y)
		{
			bool = 0;
			break;
		}
	}

	if (bool == 1)
		return matrix;

	matrix = (DataType**)realloc(matrix, (*size + 1)* sizeof(DataType*));
	matrix[*size] = CreateDataType(*size);
	Add(x, matrix[*size]);
	Add(y, matrix[*size]);
	Add(*size, matrix[x]);
	Add(*size, matrix[y]);

	*size = *size + 1;
	return matrix;
}

#pragma endregion

#pragma region Third Number
int** Union(int** matrix1, int size1, int** matrix2, int size2, int* outSize)
{
	int bSize = (size1 > size2) ? size1 : size2;
	int** bMatrix = (size1 > size2) ? matrix1 : matrix2;

	int lSize = (size1 > size2) ? size2 : size1;
	int** lMatrix = (size1 > size2) ? matrix2 : matrix1;

	int** uMatrix = GenerateMatrix(bSize, bSize);

	for (size_t i = 0; i < bSize; i++)
	{
		for (size_t j = 0; j < bSize; j++)
		{
			int res = 0;
			if (i >= lSize || j >= lSize)
				res = bMatrix[i][j];
			else
				res = lMatrix[i][j] + bMatrix[i][j] >= 1 ? 1 : 0;
			uMatrix[i][j] = res;
		}
	}

	*outSize = bSize;
	return uMatrix;
}

int** Intersection(int** matrix1, int size1, int** matrix2, int size2, int* outSize)
{
	int bSize = (size1 > size2) ? size1 : size2;
	int** bMatrix = (size1 > size2) ? matrix1 : matrix2;

	int lSize = (size1 > size2) ? size2 : size1;
	int** lMatrix = (size1 > size2) ? matrix2 : matrix1;

	int** iMatrix = GenerateMatrix(bSize, bSize);

	for (size_t i = 0; i < lSize; i++)
	{
		for (size_t j = 0; j < lSize; j++)
		{
			int res = lMatrix[i][j] * bMatrix[i][j];
			iMatrix[i][j] = res;
		}
	}

	*outSize = bSize;
	return iMatrix;
}

int** RoundSum(int** matrix1, int size1, int** matrix2, int size2, int* outSize)
{
	int bSize = (size1 > size2) ? size1 : size2;
	int** bMatrix = (size1 > size2) ? matrix1 : matrix2;

	int lSize = (size1 > size2) ? size2 : size1;
	int** lMatrix = (size1 > size2) ? matrix2 : matrix1;

	int** dMatrix = GenerateMatrix(lSize, lSize);

	for (size_t i = 0; i < lSize; i++)
	{
		for (size_t j = 0; j < lSize; j++)
		{
			int res = lMatrix[i][j] == bMatrix[i][j] ? 0 : 1;
			dMatrix[i][j] = res;
		}
	}

	int rsSize = lSize;
	int** rsMatrix = dMatrix;
	for (size_t i = 0; i < lSize; i++)
	{
		int c = 0;
		for (size_t j = 0; j < lSize; j++)
		{
			if (dMatrix[i][j] == 0)
				c++;
		}
		if (c == lSize)
			rsMatrix = RemoveVertex(rsMatrix, &rsSize, i);
	}

	*outSize = rsSize;
	return rsMatrix;
}

#pragma endregion

#pragma region Fourth Number
int** Multiplication(int** matrix1, int size1, int** matrix2, int size2, int* sizeOut)
{
	*sizeOut = size1 * size2;
	int s = *sizeOut;
	int** mMatrix = GenerateMatrix(s, s);

	int bSize = (size1 > size2) ? size1 : size2;
	int** bMatrix = (size1 > size2) ? matrix1 : matrix2;

	int lSize = (size1 > size2) ? size2 : size1;
	int** lMatrix = (size1 > size2) ? matrix2 : matrix1;

	//int n = 0, m = 0;
	//for (size_t i = 0; i < lSize; i++)
	//{
	//	for (size_t k = 0; k < bSize; k++)
	//	{
	//		for (size_t j = 0; j < lSize; j++)
	//		{
	//			for (size_t l = 0; l < bSize; l++)
	//			{
	//				if (i == j)
	//				{
	//					if (bMatrix[k][l] == 1)
	//						mMatrix[n][m] = 1;
	//				}
	//				else if (k == l)
	//				{
	//					if(lMatrix[i][j] == 1)
	//						mMatrix[n][m] = 1;
	//				}
	//				m++;
	//			}
	//		}
	//		n++;
	//		m = 0;
	//	}
	//}
	int z1 = 0, v1 = 0;
	int z2 = 0, v2 = 0;
	for (size_t i = 0; i < s; i++)
	{
		// строки
		if (i / bSize != z1)
			z1++;
		if (z1 >= lSize)
			z1 = 0;
		
		if (v1 >= bSize)
			v1 = 0;

		for (size_t j = 0; j < s; j++)
		{
			// столбцы
			if (j / bSize != z2)
				z2++;
			
			if (v2 >= bSize)
				v2 = 0;

			if (z1 == z2)
			{
				if (bMatrix[v1][v2] == 1)
					mMatrix[i][j] = 1;
			}
			else if (v1 == v2)
			{
				if (lMatrix[z1][z2] == 1)
					mMatrix[i][j] = 1;
			}
			v2 += 1;
		}
		z2 = 0;
		v2 = 0;
		v1 += 1;
	}

	return mMatrix;
}
#pragma endregion
