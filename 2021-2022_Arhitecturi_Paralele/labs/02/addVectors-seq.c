#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int* a;
int* b;
int* c;

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++) {
		a[i] = i%500;
		b[i] = i%500;
	}
}

void printPartial()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i ", c[i]);
	printf("\n");
	for(i = 20; i < N; i+=N/10)
		printf("%i ", c[i]);
	printf("\n");
	for(i = N - 10; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void printAll()
{
	int i;
	for(i = 0; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	int i, j;
	getArgs(argc, argv);
	init();

	for(j = 0; j < NReps; j++)
		for(i = 0; i < N; i++)
			c[i] = a[i] + b[i];

	print();

	return 0;
}
