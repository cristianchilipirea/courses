#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 4

typedef struct partialSolution
{
    int sudokuMatrix[N][N];
    int row;
    int column;
} partialSolution;

partialSolution readSudoku(const char *filename)
{
    char line[32];
    partialSolution ps;
    FILE *f = fopen(filename, "r");
    if (feof(f))
        return ps;

    if (f == NULL)
        return ps;

    int i = 0, j = 0;
    ps.row = -1;
    ps.column = -1;
    while (fgets(line, sizeof(line), f) != NULL)
    {
        char *token = strtok(line, " ");
        j = 0;
        while (token != NULL)
        {
            ps.sudokuMatrix[i][j++] = token[0] - 0x30;
            token = strtok(NULL, " ");
        }
        i++;
    }

    fclose(f);
    return ps;
}

void printSudoku(partialSolution ps)
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", ps.sudokuMatrix[i][j]);
        printf("\n");
    }
}

partialSolution canIncreaseStep(partialSolution PS)
{
    // are there any emply boxes left?
}

int canReject(partialSolution PS)
{
    //not all numbers are in each line, column and box
}

int isUsed(partialSolution PS, int number)
{
    //check line, column and box if number already exists
}
int isSolution(partialSolution PS)
{
    //check if all boxes are filled and each line, column and box respect the rule(each number just onces)
}
partialSolution increaseStep(partialSolution PS)
{
    //try filling the next emply box
}

partialSolution getNextChoiceAtStep(partialSolution PS)
{

}

int hasChoiceAtStep(partialSolution PS)
{

}
void backtracking(partialSolution PS)
{
    if (canReject(PS))
        return;
    if (isSolution(PS))
        printSudoku(PS);
    PS = increaseStep(PS);
    while (hasChoiceAtStep(PS))
    {
        PS = getNextChoiceAtStep(PS);
        backtracking(PS);
    }
}

int main()
{
    partialSolution PS = readSudoku("input.txt");

    backtracking(PS);

    return 0;
}