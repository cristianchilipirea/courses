#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// clang-format off
/*
//Run: mpirun -np 5 ./a.out
// DO NOT USE DIRECTLY. USE getNeighbors() INSTEAD
int graph[][2] = { { 0, 1 }, { 1, 0 }, 
                   { 2, 1 }, { 1, 2 },
                   { 3, 1 }, { 1, 3 },
				   { 3, 4 }, { 4, 3 } };
*/

//Run: mpirun -np 12 ./a.out
// DO NOT USE DIRECTLY. USE getNeighbors() INSTEAD
int graph[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, 
                   { 3, 4 }, { 4,11 }, {11, 5 }, 
                   { 5, 6 }, { 6, 7 }, { 7, 8 },
                   { 8, 9 }, { 9,10 }, {10, 9 },
                   { 9, 8 }, { 8, 7 }, { 7, 6 },
                   { 6, 5 }, { 5,11 }, {11, 4 },
                   { 4, 3 }, { 3, 2 }, { 2, 1 },
                   { 1, 0 }, { 9, 5 }, { 5, 9 },
                   { 5, 3 }, { 3, 5 }, { 0, 2 },
                   { 2, 0 }, { 9, 7 }, { 7, 9 } };

// clang-format on

// getNeighbors returns a 100 int vector.
// position 0 represents the number of neighbors
// positions 1+ represent the ranks of the neighbors
// your program should only send messages to processes on this list
int *getNeighbors(int myRank)
{
	int *neigh = malloc(sizeof(int) * 100);
	int i;
	int j = 1;
	int sizeOfGraph = sizeof(graph) / sizeof(int) / 2;
	for (i = 0; i < sizeOfGraph; i++) {
		if (graph[i][0] == myRank) {
			neigh[j] = graph[i][1];
			j++;
		}
	}
	neigh[0] = j;
	return neigh;
}

void printNeighbors(int *neigh, int rank)
{
	char aux[1000];
	aux[0] = 0;
	sprintf(aux + strlen(aux), "Rank %2i neighbors: ", rank);
	for (int i = 1; i < neigh[0]; i++) {
		sprintf(aux + strlen(aux), " %2i,", neigh[i]);
	}
	sprintf(aux + strlen(aux) - 1, "\n");  // also deletes the last comma
	printf("%s", aux);
}

int main(int argc, char *argv[])
{
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	int *neigh = getNeighbors(rank);
	printNeighbors(neigh, rank);

	// YOU ARE ONLY ALLOWED TO COMMUNICATE WITH NEIGHBOR PROCESSES

	MPI_Finalize();
	return 0;
}