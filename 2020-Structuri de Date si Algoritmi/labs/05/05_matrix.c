#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int mat[10][20];
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			mat[i][j] = 1;
	printf("%i\n", mat[3][3]);
	return 0;
}