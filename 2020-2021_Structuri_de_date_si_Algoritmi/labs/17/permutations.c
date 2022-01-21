#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 3

//PERMUTARI
typedef struct partialSolution {
	int originalVector[N] = { 0, 2, 4 };
	int permutation[N] = { -1,-1,-1 };
	int position = -1;
	int step = -1;
}partialSolution;

int canReject(partialSolution PS) {
}

int isSolution(partialSolution PS) {
}

void printSolution(partialSolution PS) {
}

partialSolution increaseStep(partialSolution PS) {
}

partialSolution getNextChoiceAtStep(partialSolution PS) {
}

int hasChoiceAtStep(partialSolution PS) {
}

void backtracking(partialSolution PS) {
	if (canReject(PS))
		return;
	if (isSolution(PS))
		printSolution(PS);
	PS = increaseStep(PS);
	while (hasChoiceAtStep(PS)) {
		PS = getNextChoiceAtStep(PS);
		backtracking(PS);
	}
}


int main()
{
	partialSolution initialValues;
	backtracking(initialValues);
	return 0;
}