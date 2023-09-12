#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Exercize1()
{
	printf("\n");
	for (int i = 0; i < 100; i++)
	{
		for (size_t j = 0; j < 100; j++)
		{
			printf("A");
		}
	}
	printf("\n");
}

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
	printf("%f", CalculateSpeed(Exercize1));
	return 0;
}