===== Lab 12 Backtracking =====

  - Folosind backtracking afișați toate permutările unui set de numere dat.
  - Folosind backtracking afișați toate submulțimile unui set de numere dat.
  - Folosind backtracking implementați problema reginelor.
**Pentru curajoși**
  - Folosind backtracking implementați problema comis voiajorului.

<code c backtracking.c>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
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

//SUBMULTIMI
typedef struct partialSolution {
	int originalVector[N] = { 0, 2, 4, 8 };
	int selector[N] = { -1,-1,-1, -1 };
	int position = -1;
	int step = -1;
}partialSolution;

//REGINE
typedef struct partialSolution {
	int queens[N] = { -1,-1,-1, -1 };
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
</code>

<code c outputPermutari.txt>
  0   2   4
  0   4   2
  2   0   4
  2   4   0
  4   0   2
  4   2   0
</code>

<code c outputSubmultimi.txt>
  8
  4
  4   8
  2
  2   8
  2   4
  2   4   8
  0
  0   8
  0   4
  0   4   8
  0   2
  0   2   8
  0   2   4
  0   2   4   8
</code>

<code c outputRegine.txt>
  1   3   0   2
  2   0   3   1
</code>