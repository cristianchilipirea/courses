#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

void selectionSort(int** v, int start, int end)
{
}

int main(int argc, char* argv[])
{
	int N = 64;
	int *v, *vQSort;
	v = (int*)malloc(sizeof(int) * N);
	vQSort = (int*)malloc(sizeof(int) * N);
	if (v == NULL || vQSort == NULL)
		return 0;
	srand(42);
	for (int i = 0; i < N; i++) {
		v[i] = rand() % N;
		vQSort[i] = v[i];
	}

	qsort(vQSort, N, sizeof(int), cmp);
	for (int i = 0; i < N; i++)
		printf("%3i ", vQSort[i]);
	printf("\n");

	selectionSort(&v, 0, N);
	int isSorted = 1;
	for (int i = 0; i < N; i++) {
		printf("%3i ", v[i]);
		if (vQSort[i] != v[i])
			isSorted = 0;
	}
	printf("\n");

	if (isSorted)
		printf("Este sortat corect\n");
	else
		printf("NU este sortat corect\n");
	return 0;
}