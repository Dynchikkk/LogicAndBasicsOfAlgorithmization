#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>	
#include <algorithm>
#include <string>
#include <cstring>
#include <numeric>

#include <queue>

#define INF 10;
//#define CONSOLE

int** GenerateMatrix(int size_x, int size_y);
void ClearMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size_x, int size_y);

int** GenerateMatrixDirected(int size, bool vz);
int** GenerateMatrixUnDirected(int size, bool vz);

void BFS(int** matrix, int size, int in, int out);

int FindRadius(int** matrix, int size);
int FindDiametr(int** matrix, int size);

void FindCenterVert(int** matrix, int size);
void FindPerefVert(int** matrix, int size);

void FindCenterOfGrav(int** matrix, int size);

int main(int argc, char* argv[])
{
	srand(time(NULL));

	const int size = 4;
	int in = 0, out = 0;
	int vz = 1, dir = 1;

	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "-vertIn") == 0)
				in = std::stoi(argv[i + 1]);
			else if (strcmp(argv[i], "-vertOut") == 0)
				out = std::stoi(argv[i + 1]);
			else if (strcmp(argv[i], "-vz") == 0)
				vz = std::stoi(argv[i + 1]);
			else if (strcmp(argv[i], "-dir") == 0)
				dir = std::stoi(argv[i + 1]);
		}

		printf("\nIn and out vertex: %d %d\n", in, out);
	}
	else
	{
		printf("Vzvesh? Directed? (0 - false, 1 - true):");
		scanf("%d %d", &vz, &dir);
	}

	if (dir == 1)
	{
		int** matrixDir = GenerateMatrixDirected(size, vz == 1 ? true : false);
		printf("Directed Matrix: \n");
		PrintMatrix(matrixDir, size, size);

		printf("\nrad = %d, diam = %d\n", FindRadius(matrixDir, size), FindDiametr(matrixDir, size));
		printf("Center vert: ");
		FindCenterVert(matrixDir, size);
		printf("Peref vert: ");
		FindPerefVert(matrixDir, size);
		FindCenterOfGrav(matrixDir, size);

		if (argc <= 1)
		{
			printf("\nInsert in and out vertex: ");
			scanf("%d %d", &in, &out);
		}

		printf("\nWay in direct matrix: ");
		BFS(matrixDir, size, in, out);
	}
	else
	{
		int** matrixUnDir = GenerateMatrixUnDirected(size, vz == 1 ? true : false);
		printf("\nUnDirected Matrix: \n");
		PrintMatrix(matrixUnDir, size, size);

		printf("\nrad = %d, diam = %d\n", FindRadius(matrixUnDir, size), FindDiametr(matrixUnDir, size));
		printf("Center vert: ");
		FindCenterVert(matrixUnDir, size);
		printf("Peref vert: ");
		FindPerefVert(matrixUnDir, size);
		FindCenterOfGrav(matrixUnDir, size);

		if (argc <= 1)
		{
			printf("\nInsert in and out vertex: ");
			scanf("%d %d", &in, &out);
		}

		printf("Way in undirect matrix: ");
		BFS(matrixUnDir, size, in, out);
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
#pragma endregion

#pragma region  MatrixGenerate
int** GenerateMatrixUnDirected(int size, bool vz)
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

			int rnd = rand() % INF;
			if (vz == false)
				rnd = rand() % 2;
			int isZero = rand() % 2;
			if (isZero == 0)
				rnd = 0;

			matrix[i][j] = rnd;
			matrix[j][i] = rnd;
		}
	}

	return matrix;
}

int** GenerateMatrixDirected(int size, bool vz)
{
	int** matrix = GenerateMatrix(size, size);

	if (matrix == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;

			int rnd = rand() % INF;
			if (vz == false)
				rnd = rand() % 2;

			int side = rand() % 3;

			switch (side)
			{
				case 0:
					matrix[i][j] = rnd;
					break;

				case 1:
					matrix[j][i] = rnd;
					break;

				case 2:
					matrix[i][j] = rnd;
					matrix[j][i] = rnd;
					break;
			}
		}
	}

	return matrix;
}
#pragma endregion

#pragma region FirsNumber
std::vector<int> BFSLogic(int** matrix, int size, int in, int out)
{
	std::vector<int> dst (size, INT_MAX);
	std::vector<int> pr (size, -1);

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>>> q;

	dst[in] = 0;
	q.push({ 0, in });

	while (!q.empty())
	{
		std::pair<int, int> tmp = q.top();
		q.pop();

		int len = tmp.first;
		int vert = tmp.second;

		if (dst[vert] < len)
			continue;

		for (int i = 0; i < size; i++)
		{
			if (matrix[vert][i] != 0)
			{
				int cur = i;
				int lenCur = matrix[vert][i];

				int nLen = len + lenCur;
				
				if (nLen < dst[cur])
				{
					dst[cur] = nLen;
					pr[cur] = vert;
					q.push({nLen, cur});
					
				}
			}
		}
	}

	int cur = out;
	std::vector<int> path;
	path.push_back(cur);

	while (pr[cur] != -1)
	{
		cur = pr[cur];
		path.push_back(cur);
	}

	int len = dst[out];
	if (len == INT_MAX)
		len = 0;
	path.push_back(len);

	std::reverse(path.begin(), path.end());

	return path;
}

void BFS(int** matrix, int size, int in, int out)
{
	std::vector<int> path = BFSLogic(matrix, size, in, out);

	if (path[0] <= 0)
		printf("There is no way");
	else
	{
		printf("Way: ");
		for (int i = 1; i < path.size(); i++)
		{
			printf("%d ", path[i]);
		}
		printf("Len: %d", path[0]);
	}

	printf("\n");
}
#pragma endregion

#pragma region SecondNumber
std::vector<int> MaxWeight(int** matrix, int size)
{
	std::vector<int> m(size, 0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int len = BFSLogic(matrix, size, i, j)[0];
			m[i] = std::max(m[i], len);
		}
	}

	return m;
}

int FindRadius(int** matrix, int size)
{
	int rad = INF + 1;
	
	std::vector<int> m = MaxWeight(matrix, size);
	
	for (size_t i = 0; i < size; i++)
	{
		rad = std::min(m[i], rad);
	}

	return rad;
}

int FindDiametr(int** matrix, int size)
{
	int diam = 0;

	std::vector<int> m = MaxWeight(matrix, size);

	for (size_t i = 0; i < size; i++)
	{
		diam = std::max(m[i], diam);
	}

	return diam;
}

void FindCenterVert(int** matrix, int size)
{
	std::vector<int> m = MaxWeight(matrix, size);
	int rad = FindRadius(matrix, size);

	for (size_t i = 0; i < size; i++)
	{
		if (m[i] == rad)
			printf("%d ", i);
	}

	printf("\n");
}

void FindPerefVert(int** matrix, int size)
{
	std::vector<int> m = MaxWeight(matrix, size);
	int diam = FindDiametr(matrix, size);

	for (size_t i = 0; i < size; i++)
	{
		if (m[i] == diam)
			printf("%d ", i);
	}

	printf("\n");
}

#pragma endregion

#pragma region Dop
std::vector<int> FindDist(int** matrix, int size, int in)
{
	std::vector<int> w(size, 0);
	for (size_t i = 0; i < size; i++)
	{
		int len = BFSLogic(matrix, size, in, i)[0];
		w[i] = len;
	}

	return w;
}

void FindCenterOfGrav(int** matrix, int size)
{
	std::vector<int> w(size, 0);
	for (size_t i = 0; i < size; i++)
	{
		std::vector<int> m = FindDist(matrix, size, i);
		printf("Dist %d: ", i);
		for (size_t j = 0; j < size; j++)
		{
			printf("%d ", m[j]);
			w[i] += m[j];
		}
		printf("\n");
	}

	int min = w[0];
	int cov = 0;
	for (size_t i = 1; i < size; i++)
	{
		if (w[i] < min)
		{
			cov = i;
			min = w[i];
		}
	}

	printf("Center of Gravity = %d, Weight = %d\n", cov, min);
}
#pragma endregion



