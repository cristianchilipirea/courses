#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int N;
int printLevel;

void getArgs(int argc, char **argv)
{
	if (argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=verbouse, 2=partial\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

void printAll()
{
	// Print Pi
}

void print()
{
	if (printLevel == 0)
		return;
	else
		printAll();
}

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	printf("Hello World from %i/%i \n", rank, nProcesses);

	if (rank == 0)
		getArgs(argc, argv);

	if (rank == 0)
		print();

	MPI_Finalize();
	return 0;
}