//USE ME AS SEQ_PROGRAM FOR SCRIPT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

int N;
int printLevel;

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);
	printf("I finished Correctly\n");

	return 0;
}
