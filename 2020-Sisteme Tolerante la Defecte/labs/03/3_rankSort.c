#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int N;
int printLevel;
int *v;
int *vQSort;

void getArgs(int argc, char **argv)
{
	if (argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=verbouse, 2=partial\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

void compareVectors(int *a, int *b)
{
	// DO NOT MODIFY
	int i;
	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int *v)
{
	// DO NOT MODIFY
	int i;
	int displayWidth = 2 + log10(N);
	for (i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b)
{
	// DO NOT MODIFY
	int A = *(int *)a;
	int B = *(int *)b;
	return A - B;
}

void printPartial()
{
	compareVectors(v, vQSort);
}

void printAll()
{
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v, vQSort);
}

void print()
{
	if (printLevel == 0)
		return;
	else if (printLevel == 2)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);

	int sorted = 0;
	int aux;
	v = (int *)malloc(sizeof(int) * N);
	vQSort = (int *)malloc(sizeof(int) * N);
	int i;

	// generate the vector v with random values
	// DO NOT MODIFY
	srand(42);
	for (i = 0; i < N; i++)
		v[i] = i;
	// replace with v[i] = rand() % N; if we are willing to accept duplicates

	for (i = 0; i < 5 * N; i++) {
		int iA = rand() % N;
		int iB = rand() % N;
		int aux;
		aux = v[iA];
		v[iA] = v[iB];
		v[iB] = aux;
	}

	// make copy to check it against qsort
	// DO NOT MODIFY
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// sort the vector v
	// REPLACE THIS WITH YOUR DISTRIBUTED SORT
	while (!sorted) {
		sorted = 1;
		for (i = 0; i < N - 1; i++) {
			if (v[i] > v[i + 1]) {
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sorted = 0;
			}
		}
	}

	print();

	return 0;
}