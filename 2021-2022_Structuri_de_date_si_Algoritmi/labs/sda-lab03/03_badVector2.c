#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int N = 100;
	int* v = malloc(N);
	for (int i = 0; i < N; i++)
		v[i] = 1;
	return 0;
}