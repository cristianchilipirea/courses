#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
long long* v;
long long sum;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

long long * allocVector(int N) {
	long long *v = malloc(sizeof(long long) * N);
	if(v == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	return v;
}

void init()
{
	v = allocVector(N);

	long long i;
	for(i = 0; i < N; i++) {
		v[i] = i+1;
	}
}

void printPartial()
{
	printf("Sum: %lli \n", sum);
}

void printAll()
{
	printPartial();
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
	getArgs(argc, argv);
	init();

	long long i;

	for(i = 0; i < N; i++)
		sum += v[i];

	print();

	return 0;
}
