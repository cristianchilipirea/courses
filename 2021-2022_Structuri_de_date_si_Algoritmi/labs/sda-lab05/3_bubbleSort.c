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
    // O(N^2)
    for (int i = 0; i < N - 1; i++)
    	for (int j = 0; j < N - i - 1; j++)
    	{
    		if (a[j] > a[j + 1])
    		{
    			aux = a[j];
    			a[j] = a[j + 1];
    			a[j + 1] = aux;
    		}
    	}
*/