#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printLevel;

void compareVectors(int *a, int *b, int N)
{
	// DO NOT MODIFY
	for (int i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int *v, int N)
{
	// DO NOT MODIFY
	int displayWidth = 2 + log10(N);
	for (int i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
		if (!((i + 1) % 20))
			printf("\n");
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

void getArgs(int argc, char **argv, int *N, int *printLevel)
{
	// DO NOT MODIFY
	if (argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	*N = atoi(argv[1]);
	*printLevel = atoi(argv[2]);
}

int *alocVector(int N)
{
	// DO NOT MODIFY
	int *aux = (int *)malloc(sizeof(int) * N);
	if (aux == NULL)
		exit(1);
	return aux;
}

void initVector(int *v, int N)
{
	// DO NOT MODIFY
	srand(42);
	for (int i = 0; i < N; i++) {
		v[i] = 2 * i;
	}

	for (int i = 0; i < 2 * N; i++) {
		int a = rand() % N;
		int b = rand() % N;
		int aux = v[a];
		v[a] = v[b];
		v[b] = aux;
	}
}

void copyVector(int *source, int *destination, int N)
{
	// DO NOT MODIFY
	for (int i = 0; i < N; i++) {
		destination[i] = source[i];
	}
}

void printPartial()  //TODO add whatever parameters you see fit
{
	//TODO
}

void printAll()  //TODO add whatever parameters you see fit
{
	//TODO
}

void print(int printLevel)
{
	// DO NOT MODIFY
	if (printLevel == -1)
		return;
	else if (printLevel == 0)
		printPartial();
	else
		printAll();
}

void sortIntDesc()  //TODO add whatever parameters you see fit
{
	//TODO
}

int main(int argc, char *argv[])
{
	int N, printLevel;
	getArgs(argc, argv, &N, &printLevel);

	//TODO

	print(printLevel);
	return 0;
}