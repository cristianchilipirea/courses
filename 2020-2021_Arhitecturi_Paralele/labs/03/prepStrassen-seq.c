#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int A11, A12, A21, A22, B11, B12, B21, B22;
int M1, M2, M3, M4, M5, M6, M7;
int C11, C12, C21, C22;

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

void init()
{
	A11 = 3213215;
	A12 = 5454;
	A21 = 5456;
	A22 = 9898;
	B11 = 54544;
	B12 = 90821;
	B21 = 9807879;
	B22 = 329132;
}

void printPartial()
{
	printf("%i %i %i %i \n", C11, C12, C21, C22);
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

	M1 = (A11 + A22) * (B11 + B22);
	M2 = (A21 + A22) * B11;
	M3 = A11 * (B12 - B22);
	M4 = A22 * (B21 - B11);
	M5 = (A11 + A12) * B22;
	M6 = (A21 - A11) * (B11 + B12);
	M7 = (A12 - A22) * (B21 + B22);
	C11 = M1 + M4 - M5 + M7;
	C12 = M3 + M5;
	C21 = M2 + M4;
	C22 = M1 - M2 + M3 + M6;

	print();

	return 0;
}
