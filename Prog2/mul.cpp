#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

void multiplication(int input_size, int num_of_threads)
{
	int r = input_size, c = input_size, i, j, count = 0, sum = 0, k;
	//dynamically allocate arrays
	int** arr1 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr1[i] = (int*)malloc(c * sizeof(int));
	int** arr2 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr2[i] = (int*)malloc(c * sizeof(int));

	int** arr3 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr3[i] = (int*)malloc(c * sizeof(int));
	for (i = 0;i < r; i++)
		for (j = 0;j < c; j++)
			arr1[i][j] = count++;
	for (i = 0;i < r; i++)
		for (j = 0;j < c; j++)
			arr2[i][j] = count++;
	double x = omp_get_wtime();
	omp_set_num_threads(num_of_threads);
#pragma omp parallel for private(j, k)
	for (i = 0;i < r; i++)
		for (j = 0;j < c; j++)
			for (k = 0;k < r; k++)
				arr3[i][j] += arr1[i][k] * arr2[k][j];

	double y = omp_get_wtime();
	printf("%lf      ", y - x);
}
int main() 
{
	printf_s("Input_Size                                      No of threads\n");
	printf_s("              1               2                4                  8\n");
	for (int i = 10; i <= 1000; i = i * 10)
	{
		printf_s("%d           ", i);
		for (int j = 1; j <= 8; j = j * 2)
		{
			multiplication(i, j);
		}
		printf_s("\n");
	}
	
	return 0;
}
