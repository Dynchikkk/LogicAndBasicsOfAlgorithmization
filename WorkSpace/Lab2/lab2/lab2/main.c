#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE_1 100
#define ARRAY_SIZE_2 1000000

#pragma region Exercize1
int** CreateDoubleArray(int size)
{
	int** array = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++)
	{
		array[i] = (int*)malloc(size * sizeof(int));
	}
	return array;
}

void ClearDoubleArray(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(array[i]);
	}
	free(array);
}

void Exercize1()
{
	int i = 0, j = 0, r;
	int elem_c;
	int** a = CreateDoubleArray(ARRAY_SIZE_1);
	int** b = CreateDoubleArray(ARRAY_SIZE_1);
	int** c = CreateDoubleArray(ARRAY_SIZE_1);

	//srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < ARRAY_SIZE_1)
	{
		while (j < ARRAY_SIZE_1)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	//srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < ARRAY_SIZE_1)
	{
		while (j < ARRAY_SIZE_1)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}

	for (i = 0; i < ARRAY_SIZE_1; i++)
	{
		for (j = 0; j < ARRAY_SIZE_1; j++)
		{
			elem_c = 0;
			for (r = 0; r < ARRAY_SIZE_1; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}

	ClearDoubleArray(a, ARRAY_SIZE_1);
	ClearDoubleArray(b, ARRAY_SIZE_1);
	ClearDoubleArray(c, ARRAY_SIZE_1);
}
#pragma endregion

#pragma region Exercize2
void shell(int* items, int count)
{
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
	int i, j;
	int x, y;

	i = left; j = right;

	/* выбор компаранда */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int* CopyArray(int* from, int size)
{
	int* to = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		to[i] = from[i];

	return to;
}

int array1[ARRAY_SIZE_2] = { 0 };
int* array2;

void RandomArray()
{
	for (int i = 0; i < ARRAY_SIZE_2; i++)
		array1[i] = rand() % 100 + 1;
	array2 = CopyArray(array1, ARRAY_SIZE_2);
}

void UpArray()
{
	for (int i = 0; i < ARRAY_SIZE_2; i++)
		array1[i] = i;
	array2 = CopyArray(array1, ARRAY_SIZE_2);
}

void DownArray()
{
	for (int i = 0, j = ARRAY_SIZE_2 - 1; i < ARRAY_SIZE_2; i++, j--)
		array1[i] = j;
	array2 = CopyArray(array1, ARRAY_SIZE_2);
}

void SplitArray()
{
	int secondPart = ARRAY_SIZE_2 - ARRAY_SIZE_2 * 0.5;
	for (int i = 0; i < secondPart; i++)
		array1[i] = i;
	for (int i = secondPart, j = ARRAY_SIZE_2 - 1; i < ARRAY_SIZE_2; i++, j--)
		array1[i] = j;
	array2 = CopyArray(array1, ARRAY_SIZE_2);
}

void TestSpeedShell()
{
	shell(array1, ARRAY_SIZE_2);
}

void TestSpeedQs()
{
	qs(array2, 0, ARRAY_SIZE_2 - 1);
}

void TestSpeedDefault()
{
	//qsort(array1, )
}
#pragma endregion


double CalculateSpeed(void (*func)())
{
	double time_spent = 0.0;

	clock_t begin = clock();
	func();
	clock_t end = clock();

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

int main()
{
	srand(time(NULL));

	printf("----- Exercize 1 -----\n");
	printf("Time spend: %fsec\n", CalculateSpeed(Exercize1));

	//
	printf("\n----- Exercize 2 -----\n");
	printf("--Random Array--\n");
	RandomArray();
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));

	printf("--Raise Array--\n");
	UpArray();
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));

	printf("--Down Array--\n");
	DownArray();
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));

	printf("--Split Array--\n");
	SplitArray();
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));;

	return 0;
}