#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int N;
int printLevel;

typedef struct partialSolution {
	int* queens;
	int position;
	int step;
}partialSolution;

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

int canReject(partialSolution PS) {
	for (int i = 0; i < PS.step; i++) {
		if (PS.queens[i] == PS.queens[PS.step])
			return 1;
		if (PS.queens[i] - PS.queens[PS.step] == i - PS.step)
			return 1;
		if (PS.queens[PS.step] - i == PS.queens[i] - PS.step)
			return 1;
	}
	return 0;
}

int isSolution(partialSolution PS) {
	if (PS.step < N - 1)
		return 0;
	return !canReject(PS);
}

void printAll(partialSolution PS) {
	for (int i = 0; i < N; i++)
		printf("%3i ", PS.queens[i]);
	printf("\n");
}

void print(partialSolution PS)
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printAll(PS);
	else
		printAll(PS);
}

partialSolution increaseStep(partialSolution PS) {
	partialSolution newPS;
	newPS.queens = malloc(sizeof(int) * N);
	memcpy(newPS.queens, PS.queens, sizeof(int) * N);
	newPS.step = PS.step+1;
	newPS.position = 0;
	return newPS;
}

partialSolution getNextPartialSolution(partialSolution PS) {
	partialSolution newPS;
	newPS.queens = malloc(sizeof(int) * N);
	memcpy(newPS.queens, PS.queens, sizeof(int) * N);
	newPS.queens[PS.step]++;
	newPS.position = PS.position+1;
	newPS.step = PS.step;
	return newPS;
}

int hasSolutionAtStep(partialSolution PS) {
	return (PS.step < N) && (PS.position < N);
}

void backtracking(partialSolution PS) {
	if (canReject(PS))
		return;
	if (isSolution(PS))
		print(PS);
	PS = increaseStep(PS);
	while (hasSolutionAtStep(PS)) {
		PS = getNextPartialSolution(PS);
		backtracking(PS);
	}
}


int main(int argc, char** argv)
{
	getArgs(argc, argv);
	partialSolution initialValues;
	initialValues.queens = malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++)
		initialValues.queens[i] = -1;
	initialValues.position = -1;
	initialValues.step = -1;
	backtracking(initialValues);
	return 0;
}