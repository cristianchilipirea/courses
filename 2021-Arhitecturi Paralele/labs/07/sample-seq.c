#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>

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

void printSomething(int task_id) {
	if(printLevel)
		printf("Something %i\n", task_id);
	if(task_id>=N) {
		return;
	}
	printSomething(task_id+1);
}

int main(int argc, char** argv)
{
	getArgs(argc, argv);
	printSomething(0);

	return 0;
}
