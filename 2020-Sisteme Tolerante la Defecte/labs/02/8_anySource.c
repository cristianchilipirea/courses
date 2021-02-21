#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i \n", rank, nProcesses);
	if (rank == 0)
		printf("A special hello message from the FIRST process\n");
	if (rank == nProcesses - 1)
		printf("A special hello message from the LAST process\n");
	MPI_Finalize();
	return 0;
}