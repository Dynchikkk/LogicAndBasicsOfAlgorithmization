#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double CalculateSpeed(void (*func)(int, ...), int* array, int size)
{
	double time_spent = 0.0;

	clock_t begin = clock();
	func(size, array);
	clock_t end = clock();

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	return time_spent;
}

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

void Exercize1(int size)
{
	int i = 0, j = 0, r;
	int elem_c;
	int** a = CreateDoubleArray(size);
	int** b = CreateDoubleArray(size);
	int** c = CreateDoubleArray(size);

	//srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < size)
	{
		while (j < size)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	//srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < size)
	{
		while (j < size)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			elem_c = 0;
			for (r = 0; r < size; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}

	ClearDoubleArray(a, size);
	ClearDoubleArray(b, size);
	ClearDoubleArray(c, size);
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

void RandomArray(int size, int* arr1, int* arr2, int* arr3)
{
	*arr1 = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		arr1[i] = rand() % 100 + 1;
	*arr2 = CopyArray(arr1, size);
	*arr3 = CopyArray(arr1, size);
}

void UpArray(int size, int* arr1, int* arr2, int* arr3)
{
	*arr1 = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		arr1[i] = i;
	*arr2 = CopyArray(arr1, size);
	*arr3 = CopyArray(arr1, size);
}

void DownArray(int size, int* arr1, int* arr2, int* arr3)
{
	*arr1 = (int*)malloc(size * sizeof(int));

	for (int i = 0, j = size - 1; i < size; i++, j--)
		arr1[i] = j;
	*arr2 = CopyArray(arr1, size);
	*arr3 = CopyArray(arr1, size);
}

void SplitArray(int size, int* arr1, int* arr2, int* arr3)
{
	*arr1 = (int*)malloc(size * sizeof(int));

	int secondPart = size - size * 0.5;
	for (int i = 0; i < secondPart; i++)
		arr1[i] = i;
	for (int i = secondPart, j = size - 1; i < size; i++, j--)
		arr1[i] = j;
	*arr2 = CopyArray(arr1, size);
	*arr3 = CopyArray(arr1, size);
}

int compare(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);
}

void TestSpeedShell(int size, int* array)
{
	shell(array, size);
}

void TestSpeedQs(int size, int* array)
{
	qs(array, 0, size - 1);
}

void TestSpeedDefault(int size, int* array)
{
	qsort(array, size, sizeof(int), compare);
}

void autoTest(int size)
{
	int* array1 = (int*)malloc(size * sizeof(int));
	int* array2= (int*)malloc(size * sizeof(int));
	int* array3 = (int*)malloc(size * sizeof(int));

	printf("----- Size %d -----\n", size);

	printf("--Random Array--\n");
	RandomArray(size, array1, array2, array3);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell, array1, size));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs, array2, size));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault, array3, size));

	printf("--Raise Array--\n");
	UpArray(size, array1, array2, array3);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell, array1, size));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs, array2, size));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault, array3, size));

	printf("--Down Array--\n");
	DownArray(size, array1, array2, array3);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell, array1, size));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs, array2, size));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault, array3, size));

	printf("--Split Array--\n");
	SplitArray(size, array1, array2, array3);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell, array1, size));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs, array2, size));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault, array3, size));

	free(array1);
	free(array2);
	free(array3);

	printf("\n");
}
#pragma endregion

int main()
{
	srand(time(NULL));

	int size = 0;
	printf("Insert array size for ex1: ");
	scanf("%d", &size);

	printf("----- Exercize 1 -----\n");
	printf("Time spend: %fsec\n", CalculateSpeed(Exercize1, NULL, size));

	printf("\n----- Exercize 2 -----\n");
	for (int i = 10000; i < 100000; i+= 10000)
	{
		autoTest(i);
	}

	return 0;
}
