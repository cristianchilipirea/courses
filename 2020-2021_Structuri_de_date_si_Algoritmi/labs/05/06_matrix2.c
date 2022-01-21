#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int** mat = malloc(sizeof(int*) * 200);
	for (int i = 0; i < 100; i++)
		mat[i] = malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 200; j++)
			mat[i][j] = 1;
	printf("%i\n", mat[3][3]);
	for (int i = 0; i < 100; i++)
		free(mat[i]);
	free(mat);
	return 0;
}