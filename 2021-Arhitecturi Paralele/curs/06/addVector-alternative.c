#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int printLevel;
int N;
int NReps;
int P;
int *a;
int *b;
int *c;

void *threadFunction(void *var)
{
	int thread_id = *(int *)var;

	for (int j = 0; j < NReps; j++)
		for (int i = thread_id; i < N; i += P)
			c[i] += 10;
	return NULL;
}

void getArgs(int argc, char **argv)
{
	if (argc < 4) {
		printf("Not enough paramters: ./program N NReps printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
	P = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if (c == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	int i;
	for (i = 0; i < N; i++) {
		a[i] = i;
		b[i] = i;
		c[i] = i;
	}
}

void printAll()
{
	int i;
	for (i = 0; i < N; i++) {
		printf("%i\t", c[i]);
	}
	printf("\n");
}

void printPartial()
{
	printAll();
}

void print()
{
	if (printLevel == 0)
		return;
	else if (printLevel == 1)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	int i;
	getArgs(argc, argv);
	init();

	pthread_t tid[P];
	int thread_id[P];
	for (i = 0; i < P; i++)
		thread_id[i] = i;

	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	return 0;
}