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
    // O(N log(N))
    int counter = 0;
    for (int i = 0; i < N; i++)
    	for (int j = 1; j < N; j*=2)
    			counter++;
    printf("%i\n", counter);
*/