#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE_1 100

double CalculateSpeed(void (*func)())
{
	double time_spent = 0.0;

	clock_t begin = clock();
	func();
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

int* array1;
int* array2;
int* array3;
int sizeDefault = 100;

void RandomArray(int size)
{
	for (int i = 0; i < size; i++)
		array1[i] = rand() % 100 + 1;
	array2 = CopyArray(array1, size);
	array3 = CopyArray(array1, size);
}

void UpArray(int size)
{
	for (int i = 0; i < size; i++)
		array1[i] = i;
	array2 = CopyArray(array1, size);
	array3 = CopyArray(array1, size);
}

void DownArray(int size)
{
	for (int i = 0, j = size - 1; i < size; i++, j--)
		array1[i] = j;
	array2 = CopyArray(array1, size);
	array3 = CopyArray(array1, size);
}

void SplitArray(int size)
{
	int secondPart = size - size * 0.5;
	for (int i = 0; i < secondPart; i++)
		array1[i] = i;
	for (int i = secondPart, j = size - 1; i < size; i++, j--)
		array1[i] = j;
	array2 = CopyArray(array1, size);
	array3 = CopyArray(array1, size);
}

void TestSpeedShell()
{
	shell(array1, sizeDefault);
}

void TestSpeedQs()
{
	qs(array2, 0, sizeDefault - 1);
}

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

void TestSpeedDefault()
{
	qsort(array3, sizeDefault, sizeof(int), compare);
}

void autoTest(int size)
{
	array1 = (int*)malloc(size * sizeof(int));
	sizeDefault = size;
	printf("----- Size %d -----\n", size);
	printf("--Random Array--\n");
	RandomArray(size);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault));

	printf("--Raise Array--\n");
	UpArray(size);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault));

	printf("--Down Array--\n");
	DownArray(size);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault));

	printf("--Split Array--\n");
	SplitArray(size);
	printf("Shell sort: %fsec\n", CalculateSpeed(TestSpeedShell));
	printf("Quick sort: %fsec\n", CalculateSpeed(TestSpeedQs));;
	printf("Default c sort: %fsec\n", CalculateSpeed(TestSpeedDefault));

	printf("\n");
}
#pragma endregion

int main()
{
	srand(time(NULL));

	printf("----- Exercize 1 -----\n");
	printf("Time spend: %fsec\n", CalculateSpeed(Exercize1));

	printf("\n----- Exercize 2 -----\n");
	for (int i = 0; i < 100000; i+= 10000)
	{
		autoTest(i);
	}

	return 0;
}
