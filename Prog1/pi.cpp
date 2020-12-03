#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define SEED 35791246

void observation_table(int num_of_threads, int input_size)
{
	int i, count = 0;
	double z, pi, x, y;
	omp_set_num_threads(num_of_threads);
	double t1 = omp_get_wtime();
#pragma omp parallel for
	for (i = 0; i < input_size; i++)
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x * x + y * y;
		if (z <= 1) count++;
	}
	pi = (double)count / input_size * 4;
	double t2 = omp_get_wtime();
	printf("%lf         ", t2 - t1);

}
void main()
{
	int n = 0, i, count = 0;
	double z, pi, x, y;
	printf_s("Enter the number of iterations used to estimate pi: ");
	scanf_s("%d", &n);
	srand(SEED);
	
#pragma omp parallel for
	for (i = 0; i < n; i++)
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x * x + y * y;
		if (z <= 1) count++;
	}
	pi = (double)count / n * 4;
	printf_s("# of trials= %d , estimate of pi is %g \n", n, pi);
	printf_s("Input_Size                                      No of threads\n");
	printf_s("              1               2                4                  8\n");
	for (i = 10; i <= 100000; i = i * 10)
	{
		printf_s("%d           ", i);
		for (int j = 1; j <= 8; j = j * 2)
		{
			observation_table(j, i);
		}
		printf_s("\n");
	}
}