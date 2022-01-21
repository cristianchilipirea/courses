#include <stdio.h>
#include <stdlib.h>

int func(int i)
{
	int mat[1000][1000];
	if (i > 1000)
		return 1;
	func(i + 1);
	mat[3][3] = 2;
	return mat[3][3];
}

int main(int argc, char* argv[])
{
	printf("%i\n", func(0));
	return 0;
}