#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Need to run with a parameter N, in VsCode you can configure to run in launch.json on the args line\n");
		return 1;
	}
	int N = atoi(argv[1]);
	printf("Hello World! N is %i\n", N);
	return 0;
}

/*

    // O(N^3)
    for (int i = 0; i < N; i++)
    	for (int j = 0; j < N; j++)
    		for (int k = 0; k < N; k++)
    			c[i][j] += a[i][k] * b[k][j];



*/