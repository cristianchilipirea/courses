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
    //O(log(N)^3)
    int counter = 0;
    int i = 1;
    while (i <= N) {
    	i = i * 2;
    	for (int j = 1; j < log10(i)/log10(2); j++)
    		for(int k=1; k<=j;k++)
    			counter++;
    }
*/